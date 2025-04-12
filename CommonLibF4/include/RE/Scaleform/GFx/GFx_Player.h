#pragma once

#include "RE/Scaleform/GFx/GFx_Loader.h"
#include "RE/Scaleform/GFx/GFx_Log.h"
#include "RE/Scaleform/GFx/GFx_PlayerStats.h"
#include "RE/Scaleform/GFx/GFx_Types.h"
#include "RE/Scaleform/Kernel/SF_RefCount.h"
#include "RE/Scaleform/Render/Render_Constants.h"
#include "RE/Scaleform/Render/Render_Context.h"
#include "RE/Scaleform/Render/Render_TreeNode.h"
#include "RE/Scaleform/Render/Render_Viewport.h"

namespace RE::Scaleform::GFx
{
	class ASMovieRootBase;
	class EventId;
	class FunctionHandler;
	class InteractiveObject;
	class MemoryContext;
	class Movie;
	class MovieDef;
	class MovieImpl;
	class Value;
	class Viewport;

	struct MemoryParams;

	class Viewport :
		public Render::Viewport
	{
	public:
		// members
		float scale;        // 2C
		float aspectRatio;  // 30
	};
	static_assert(sizeof(Viewport) == 0x34);

	class __declspec(novtable) alignas(0x08) MemoryContext :
		public RefCountBase<MemoryContext, 2>  // 00
	{
	public:
		virtual ~MemoryContext() = default;
	};
	static_assert(sizeof(MemoryContext) == 0x10);

	struct MemoryParams
	{
	public:
		// members
		MemoryHeap::HeapDesc desc;                                                        // 00
		float                heapLimitMultiplier{ 0.25F };                                // 40
		std::uint32_t        maxCollectionRoots{ static_cast<std::uint32_t>(-1) };        // 44
		std::uint32_t        framesBetweenCollections{ static_cast<std::uint32_t>(-1) };  // 48
		std::uint32_t        initialDynamicLimit{ static_cast<std::uint32_t>(-1) };       // 4C
		std::uint32_t        runsToUpgradeGen{ static_cast<std::uint32_t>(-1) };          // 50
		std::uint32_t        runsToCollectYoung{ static_cast<std::uint32_t>(-1) };        // 54
		std::uint32_t        runsToCollectOld{ static_cast<std::uint32_t>(-1) };          // 58
	};
	static_assert(sizeof(MemoryParams) == 0x60);

	class __declspec(novtable) MovieDef :
		public Resource,  // 00
		public StateBag   // 18
	{
	public:
		enum class FileAttrFlags : std::uint32_t
		{
			kUseNetwork = 1 << 0,
			kUseActionScript3 = 1 << 3,
			kHasMetadata = 1 << 4
		};

		enum class VisitResourceMask : std::uint32_t
		{
			kNestedMovies = 1 << 15,

			kFonts = 1 << 0,
			kBitmaps = 1 << 1,
			kGradientImages = 1 << 2,
			kEditTextFields = 1 << 3,
			kSounds = 1 << 4,
			kSprite = 1 << 5,

			kAllLocalImages = (kBitmaps | kGradientImages),
			kAllImages = (kBitmaps | kGradientImages | kNestedMovies)
		};

		struct __declspec(novtable) ImportVisitor
		{
		public:
			virtual ~ImportVisitor() = default;  // 00

			// add
			virtual void Visit(MovieDef* a_parentDef, MovieDef* a_importDef, const char* a_importedMovieFilename) = 0;  // 01
		};
		static_assert(sizeof(ImportVisitor) == 0x8);

		struct __declspec(novtable) ResourceVisitor :
			public FileTypeConstants  // 00
		{
		public:
			virtual ~ResourceVisitor() = default;  // 00

			// add
			virtual void Visit(MovieDef* a_movieDef, Resource* a_resource, ResourceId a_rid, const char* a_exportName) = 0;  // 01
		};
		static_assert(sizeof(ResourceVisitor) == 0x8);

		// add
		virtual std::uint32_t       GetVersion() const = 0;                                                                                                                                     // 04
		virtual std::uint32_t       GetLoadingFrame() const = 0;                                                                                                                                // 05
		virtual float               GetWidth() const = 0;                                                                                                                                       // 06
		virtual float               GetHeight() const = 0;                                                                                                                                      // 07
		virtual std::uint32_t       GetFrameCount() const = 0;                                                                                                                                  // 08
		virtual float               GetFrameRate() const = 0;                                                                                                                                   // 09
		virtual RectF               GetFrameRect() const = 0;                                                                                                                                   // 0A
		virtual std::uint32_t       GetSWFFlags() const = 0;                                                                                                                                    // 0B
		virtual const char*         GetFileURL() const = 0;                                                                                                                                     // 0C
		virtual void                WaitForLoadFinish(bool a_cancel = false) const = 0;                                                                                                         // 0D
		virtual void                WaitForFrame(std::uint32_t a_frame) const = 0;                                                                                                              // 0E
		virtual FileAttrFlags       GetFileAttributes() const = 0;                                                                                                                              // 0F
		virtual std::uint32_t       GetMetadata(char* a_buff, std::uint32_t a_buffSize) const = 0;                                                                                              // 10
		virtual MemoryHeap*         GetLoadDataHeap() const = 0;                                                                                                                                // 11
		virtual MemoryHeap*         GetBindDataHeap() const = 0;                                                                                                                                // 12
		virtual MemoryHeap*         GetImageHeap() const = 0;                                                                                                                                   // 13
		virtual Resource*           GetMovieDataResource() const = 0;                                                                                                                           // 14
		virtual const ExporterInfo* GetExporterInfo() const = 0;                                                                                                                                // 15
		virtual MemoryContext*      CreateMemoryContext(const char* a_heapName, const MemoryParams& a_memParams, bool a_debugHeap) = 0;                                                         // 16
		virtual Movie*              CreateInstance(const MemoryParams& a_memParams, bool a_initFirstFrame, ActionControl* a_actionControl, Render::ThreadCommandQueue* a_queue = nullptr) = 0;  // 18
		virtual Movie*              CreateInstance(MemoryContext* a_memContext, bool a_initFirstFrame, ActionControl* a_actionControl, Render::ThreadCommandQueue* a_queue = nullptr) = 0;      // 17
		virtual void                VisitImportedMovies(ImportVisitor* a_visitor) = 0;                                                                                                          // 19
		virtual void                VisitResources(ResourceVisitor* a_visitor, VisitResourceMask a_visitMask = VisitResourceMask::kAllImages) = 0;                                              // 1A
		virtual Resource*           GetResource(const char* a_exportName) const = 0;                                                                                                            // 1B

		[[nodiscard]] Movie* CreateInstance(
			bool                        a_initFirstFrame = false,
			std::size_t                 a_memoryArena = 0,
			ActionControl*              a_actionControl = nullptr,
			Render::ThreadCommandQueue* a_queue = nullptr)
		{
			MemoryParams memParams;
			memParams.desc.arena = a_memoryArena;
			return CreateInstance(memParams, a_initFirstFrame, a_actionControl, a_queue);
		}
	};
	static_assert(sizeof(MovieDef) == 0x20);

	class Value
	{
	public:
		enum class ValueType : std::int32_t
		{
			kUndefined,
			kNull,
			kBoolean,
			kInt,
			kUInt,
			kNumber,
			kString,

			kStringW,

			kObject,
			kArray,
			kDisplayObject,
			kClosure,

			kOrphanedBit = 1 << 5,
			kManagedBit = 1 << 6,
			kConvertBit = 1 << 7,

			kTypeMask = kConvertBit | 0x0F,

			kConvertBoolean = kConvertBit | kBoolean,
			kConvertInt = kConvertBit | kInt,
			kConvertUInt = kConvertBit | kUInt,
			kConvertNumber = kConvertBit | kNumber,
			kConvertString = kConvertBit | kString,
			kConvertStringW = kConvertBit | kStringW
		};

		union ValueUnion
		{
			ValueUnion() noexcept :
				data(nullptr)
			{}

			ValueUnion(const ValueUnion& a_rhs) noexcept :
				data(a_rhs.data)
			{}

			ValueUnion(ValueUnion&& a_rhs) noexcept :
				data(a_rhs.data)
			{
				a_rhs.data = nullptr;
			}

			explicit ValueUnion(std::int32_t a_rhs) noexcept :
				int32(a_rhs)
			{}

			explicit ValueUnion(std::uint32_t a_rhs) noexcept :
				uint32(a_rhs)
			{}

			explicit ValueUnion(double a_rhs) noexcept :
				number(a_rhs)
			{}

			explicit ValueUnion(bool a_rhs) noexcept :
				boolean(a_rhs)
			{}

			explicit ValueUnion(const char* a_rhs) noexcept :
				string(a_rhs)
			{}

			explicit ValueUnion(const wchar_t* a_rhs) noexcept :
				wstring(a_rhs)
			{}

			ValueUnion& operator=(const ValueUnion& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					data = a_rhs.data;
				}
				return *this;
			}

			ValueUnion& operator=(ValueUnion&& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					data = a_rhs.data;
					a_rhs.data = nullptr;
				}
				return *this;
			}

			ValueUnion& operator=(std::int32_t a_rhs) noexcept
			{
				int32 = a_rhs;
				return *this;
			}

			ValueUnion& operator=(std::uint32_t a_rhs) noexcept
			{
				uint32 = a_rhs;
				return *this;
			}

			ValueUnion& operator=(double a_rhs) noexcept
			{
				number = a_rhs;
				return *this;
			}

			ValueUnion& operator=(bool a_rhs) noexcept
			{
				boolean = a_rhs;
				return *this;
			}

			ValueUnion& operator=(const char* a_rhs) noexcept
			{
				string = a_rhs;
				return *this;
			}

			ValueUnion& operator=(const wchar_t* a_rhs) noexcept
			{
				wstring = a_rhs;
				return *this;
			}

			std::int32_t   int32;
			std::uint32_t  uint32;
			double         number;
			bool           boolean;
			const char*    string;
			const char**   mstring;
			const wchar_t* wstring;
			void*          data;
		};
		static_assert(sizeof(ValueUnion) == 0x8);

		class DisplayInfo
		{
		public:
			enum class SetFlags : std::uint16_t
			{
				kX = 0x01,
				kY = 0x02,
				kRotation = 0x04,
				kXScale = 0x08,
				kYScale = 0x10,
				kAlpha = 0x20,
				kVisible = 0x40,
				kZ = 0x80,
				kXRotation = 0x100,
				kYRotation = 0x200,
				kZScale = 0x400,
				kFOV = 0x800,
				kProjMatrix3D = 0x1000,
				kViewMatrix3D = 0x2000,
				kEdgeAAMode = 0x4000,
			};

			DisplayInfo() = default;

			double GetX() const
			{
				assert(varsSet.any(SetFlags::kX));
				return x;
			}

			double GetY() const
			{
				assert(varsSet.any(SetFlags::kY));
				return y;
			}

			double GetZ() const
			{
				assert(varsSet.any(SetFlags::kZ));
				return z;
			}

			double GetXScale() const
			{
				assert(varsSet.any(SetFlags::kXScale));
				return xScale;
			}

			double GetYScale() const
			{
				assert(varsSet.any(SetFlags::kYScale));
				return yScale;
			}

			double GetZScale() const
			{
				assert(varsSet.any(SetFlags::kZScale));
				return zScale;
			}

			double GetRotation() const
			{
				assert(varsSet.any(SetFlags::kRotation));
				return rotation;
			}

			double GetXRotation() const
			{
				assert(varsSet.any(SetFlags::kXRotation));
				return xRotation;
			}

			double GetYRotation() const
			{
				assert(varsSet.any(SetFlags::kYRotation));
				return yRotation;
			}

			double GetAlpha() const
			{
				assert(varsSet.any(SetFlags::kAlpha));
				return alpha;
			}

			bool GetVisible() const
			{
				assert(varsSet.any(SetFlags::kVisible));
				return visible;
			}

			double GetFOV() const
			{
				assert(varsSet.any(SetFlags::kFOV));
				return fov;
			}

			const Matrix3F* GetViewMatrix3D() const
			{
				return varsSet.any(SetFlags::kViewMatrix3D) ? &viewMatrix3D : nullptr;
			}

			const Matrix4F* GetProjectionMatrix3D() const
			{
				return varsSet.any(SetFlags::kProjMatrix3D) ? &projectionMatrix3D : nullptr;
			}

			Render::EdgeAAMode GetEdgeAAMode() const
			{
				assert(varsSet.any(SetFlags::kEdgeAAMode));
				return edgeAAMode;
			}

			void SetX(double a_x)
			{
				varsSet.set(SetFlags::kX);
				x = a_x;
			}

			void SetY(double a_y)
			{
				varsSet.set(SetFlags::kY);
				y = a_y;
			}

			void SetZ(double a_z)
			{
				varsSet.set(SetFlags::kZ);
				z = a_z;
			}

			void SetXScale(double a_xScale)
			{
				varsSet.set(SetFlags::kXScale);
				xScale = a_xScale;
			}

			void SetYScale(double a_yScale)
			{
				varsSet.set(SetFlags::kYScale);
				yScale = a_yScale;
			}

			void SetZScale(double a_zScale)
			{
				varsSet.set(SetFlags::kZScale);
				zScale = a_zScale;
			}

			void SetRotation(double a_rotation)
			{
				varsSet.set(SetFlags::kRotation);
				rotation = a_rotation;
			}

			void SetXRotation(double a_xRotation)
			{
				varsSet.set(SetFlags::kXRotation);
				xRotation = a_xRotation;
			}

			void SetYRotation(double a_yRotation)
			{
				varsSet.set(SetFlags::kYRotation);
				yRotation = a_yRotation;
			}

			void SetAlpha(double a_alpha)
			{
				varsSet.set(SetFlags::kAlpha);
				alpha = a_alpha;
			}

			void SetVisible(bool a_visible)
			{
				varsSet.set(SetFlags::kVisible);
				visible = a_visible;
			}

			void SetFOV(double a_fov)
			{
				varsSet.set(SetFlags::kFOV);
				fov = a_fov;
			}

			void SetViewMatrix3D(const Matrix3F* a_matrix)
			{
				if (a_matrix) {
					varsSet.set(SetFlags::kViewMatrix3D);
					viewMatrix3D = *a_matrix;
				} else {
					varsSet.reset(SetFlags::kViewMatrix3D);
				}
			}

			void SetProjectionMatrix3D(const Matrix4F* a_matrix)
			{
				if (a_matrix) {
					varsSet.set(SetFlags::kProjMatrix3D);
					projectionMatrix3D = *a_matrix;
				} else {
					varsSet.reset(SetFlags::kProjMatrix3D);
				}
			}

			void SetEdgeAAMode(Render::EdgeAAMode a_mode)
			{
				varsSet.set(SetFlags::kEdgeAAMode);
				edgeAAMode = a_mode;
			}

		private:
			// members
			double x;
			double y;
			double rotation;
			double xScale;
			double yScale;
			double alpha;
			double z;
			double xRotation;
			double yRotation;
			double zScale;
			double fov;
			alignas(16) Render::Matrix3x4<float> viewMatrix3D;
			Render::Matrix4x4<float> projectionMatrix3D;
			Render::EdgeAAMode       edgeAAMode;
			Flags<SetFlags>          varsSet{};
			bool                     visible;
		};
		static_assert(sizeof(DisplayInfo) == 0xE0);

		class __declspec(novtable) ObjectInterface :
			public NewOverrideBase<327>
		{
		public:
			class __declspec(novtable) ObjVisitor
			{
			public:
				virtual ~ObjVisitor() = default;  // 00

				// add
				virtual bool IncludeAS3PublicMembers() const { return false; }   // 01
				virtual void Visit(const char* a_name, const Value& a_val) = 0;  // 02
			};
			static_assert(sizeof(ObjVisitor) == 0x8);

			class __declspec(novtable) ArrVisitor
			{
			public:
				virtual ~ArrVisitor() = default;

				// add
				virtual void Visit(std::uint32_t a_idx, const Value& a_val) = 0;  // 00
			};
			static_assert(sizeof(ArrVisitor) == 0x8);

			virtual ~ObjectInterface() = default;  // 00

			void ObjectAddRef(Value* a_val, void* a_obj)
			{
				using func_t = decltype(&ObjectInterface::ObjectRelease);
				static REL::Relocation<func_t> func{ REL::ID(2286228) };
				return func(this, a_val, a_obj);
			}

			void ObjectRelease(Value* a_val, void* a_obj)
			{
				using func_t = decltype(&ObjectInterface::ObjectRelease);
				static REL::Relocation<func_t> func{ REL::ID(2286229) };
				return func(this, a_val, a_obj);
			}

			bool HasMember(void* a_data, const char* a_name, bool a_isdobj) const
			{
				using func_t = decltype(&ObjectInterface::HasMember);
				static REL::Relocation<func_t> func{ REL::ID(2286078) };
				return func(this, a_data, a_name, a_isdobj);
			}

			std::uint32_t GetArraySize(void* a_data) const
			{
				using func_t = decltype(&ObjectInterface::GetArraySize);
				static REL::Relocation<func_t> func{ REL::ID(2285791) };
				return func(this, a_data);
			}

			bool GetMember(void* a_data, const char* a_name, Value* a_val, bool a_isdobj) const
			{
				using func_t = decltype(&ObjectInterface::GetMember);
				static REL::Relocation<func_t> func{ REL::ID(2285936) };
				return func(this, a_data, a_name, a_val, a_isdobj);
			}

			bool GetElement(void* a_data, std::uint32_t a_idx, Value* a_val) const
			{
				using func_t = decltype(&ObjectInterface::GetElement);
				static REL::Relocation<func_t> func{ REL::ID(2285881) };
				return func(this, a_data, a_idx, a_val);
			}

			bool SetElement(void* a_data, std::uint32_t a_idx, const Value& a_val)
			{
				using func_t = decltype(&ObjectInterface::SetElement);
				static REL::Relocation<func_t> func{ REL::ID(2286575) };
				return func(this, a_data, a_idx, a_val);
			}

			bool SetMember(void* a_data, const char* a_name, const Value& a_value, bool a_isdobj)
			{
				using func_t = decltype(&ObjectInterface::SetMember);
				static REL::Relocation<func_t> func{ REL::ID(2286589) };
				return func(this, a_data, a_name, a_value, a_isdobj);
			}

			bool Invoke(void* a_data, Value* a_result, const char* a_name, const Value* a_args, std::size_t a_numArgs, bool a_isdobj)
			{
				using func_t = decltype(&ObjectInterface::Invoke);
				static REL::Relocation<func_t> func{ REL::ID(2286101) };
				return func(this, a_data, a_result, a_name, a_args, a_numArgs, a_isdobj);
			}

			bool PushBack(void* a_data, const Value& a_value)
			{
				using func_t = decltype(&ObjectInterface::PushBack);
				static REL::Relocation<func_t> func{ REL::ID(2286424) };
				return func(this, a_data, a_value);
			}

			bool RemoveElements(void* a_data, std::uint32_t a_idx, std::int32_t a_count)
			{
				using func_t = decltype(&ObjectInterface::RemoveElements);
				static REL::Relocation<func_t> func{ REL::ID(2286475) };
				return func(this, a_data, a_idx, a_count);
			}

			void VisitMembers(void* a_data, ObjVisitor* a_visitor, bool a_isDObj) const
			{
				using func_t = decltype(&ObjectInterface::VisitMembers);
				static REL::Relocation<func_t> func{ REL::ID(2286786) };
				return func(this, a_data, a_visitor, a_isDObj);
			}

			bool GetDisplayInfo(void* a_data, DisplayInfo* a_info) const
			{
				using func_t = decltype(&ObjectInterface::GetDisplayInfo);
				static REL::Relocation<func_t> func{ REL::ID(2285873) };
				return func(this, a_data, a_info);
			}

			// members
			MovieImpl* movieRoot;  // 08
		};
		static_assert(sizeof(ObjectInterface) == 0x10);

		using ObjectVisitor = ObjectInterface::ObjVisitor;
		using ArrayVisitor = ObjectInterface::ArrVisitor;
		using ObjectVisitFn = std::function<void(const char*, const Value&)>;

		Value() noexcept = default;

		Value(const Value& a_rhs) :
			_type(a_rhs._type),
			_value(a_rhs._value),
			_dataAux(a_rhs._dataAux)
		{
			if (a_rhs.IsManagedValue()) {
				AcquireManagedValue(a_rhs);
			}
		}

		Value(Value&& a_rhs) noexcept :
			_objectInterface(a_rhs._objectInterface),
			_type(a_rhs._type),
			_value(std::move(a_rhs._value)),
			_dataAux(a_rhs._dataAux)
		{
			a_rhs._objectInterface = nullptr;
			a_rhs._type = ValueType::kUndefined;
			a_rhs._dataAux = 0;
		}

		Value(std::nullptr_t) noexcept :
			_type(ValueType::kNull)
		{}

		Value(std::int32_t a_rhs) noexcept :
			_type(ValueType::kInt),
			_value(a_rhs)
		{}

		Value(std::uint32_t a_rhs) noexcept :
			_type(ValueType::kUInt),
			_value(a_rhs)
		{}

		Value(double a_rhs) noexcept :
			_type(ValueType::kNumber),
			_value(a_rhs)
		{}

		Value(bool a_rhs) noexcept :
			_type(ValueType::kBoolean),
			_value(a_rhs)
		{}

		Value(const char* a_rhs) noexcept :
			_type(ValueType::kString),
			_value(a_rhs)
		{}

		Value(std::string_view a_rhs) noexcept :
			_type(ValueType::kString),
			_value(a_rhs.data())
		{}

		Value(const wchar_t* a_rhs) noexcept :
			_type(ValueType::kStringW),
			_value(a_rhs)
		{}

		Value(std::wstring_view a_rhs) noexcept :
			_type(ValueType::kStringW),
			_value(a_rhs.data())
		{}

		~Value()
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kUndefined;
		}

		Value& operator=(const Value& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				if (IsManagedValue()) {
					ReleaseManagedValue();
				}

				_type = a_rhs._type;
				_value = a_rhs._value;
				_dataAux = a_rhs._dataAux;

				if (a_rhs.IsManagedValue()) {
					AcquireManagedValue(a_rhs);
				}
			}
			return *this;
		}

		Value& operator=(Value&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				if (IsManagedValue()) {
					ReleaseManagedValue();
				}

				_objectInterface = a_rhs._objectInterface;
				a_rhs._objectInterface = nullptr;

				_type = a_rhs._type;
				a_rhs._type = ValueType::kUndefined;

				_value = std::move(a_rhs._value);

				_dataAux = a_rhs._dataAux;
				a_rhs._dataAux = 0;
			}
			return *this;
		}

		Value& operator=(std::nullptr_t) noexcept
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kNull;
			return *this;
		}

		Value& operator=(std::int32_t a_rhs) noexcept
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kInt;
			_value = a_rhs;
			return *this;
		}

		Value& operator=(std::uint32_t a_rhs) noexcept
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kUInt;
			_value = a_rhs;
			return *this;
		}

		Value& operator=(double a_rhs) noexcept
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kNumber;
			_value = a_rhs;
			return *this;
		}

		Value& operator=(bool a_rhs) noexcept
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kBoolean;
			_value = a_rhs;
			return *this;
		}

		Value& operator=(const char* a_rhs) noexcept
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kString;
			_value = a_rhs;
			return *this;
		}

		Value& operator=(const wchar_t* a_rhs) noexcept
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kStringW;
			_value = a_rhs;
			return *this;
		}

		[[nodiscard]] ValueType GetType() const noexcept { return *(_type & ValueType::kTypeMask); }

		[[nodiscard]] bool IsArray() const noexcept { return GetType() == ValueType::kArray; }
		[[nodiscard]] bool IsBoolean() const noexcept { return GetType() == ValueType::kBoolean; }
		[[nodiscard]] bool IsDisplayObject() const noexcept { return GetType() == ValueType::kDisplayObject; }
		[[nodiscard]] bool IsInt() const noexcept { return GetType() == ValueType::kInt; }
		[[nodiscard]] bool IsNumber() const noexcept { return GetType() == ValueType::kNumber; }
		[[nodiscard]] bool IsString() const noexcept { return GetType() == ValueType::kString; }
		[[nodiscard]] bool IsUndefined() const noexcept { return GetType() == ValueType::kUndefined; }
		[[nodiscard]] bool IsUInt() const noexcept { return GetType() == ValueType::kUInt; }

		[[nodiscard]] bool IsObject() const noexcept
		{
			switch (GetType()) {
				case ValueType::kObject:
				case ValueType::kArray:
				case ValueType::kDisplayObject:
					return true;
				default:
					return false;
			}
		}

		[[nodiscard]] bool GetBoolean() const
		{
			assert(IsBoolean());
			return _value.boolean;
		}

		[[nodiscard]] std::int32_t GetInt() const
		{
			assert(IsInt());
			return _value.int32;
		}

		[[nodiscard]] double GetNumber() const
		{
			assert(IsNumber());
			return _value.number;
		}

		[[nodiscard]] const char* GetString() const
		{
			assert(IsString());
			return IsManagedValue() ? *_value.mstring : _value.string;
		}

		[[nodiscard]] std::uint32_t GetUInt() const
		{
			assert(IsUInt());
			return _value.uint32;
		}

		bool HasMember(stl::zstring a_name) const
		{
			assert(IsObject());
			return _objectInterface->HasMember(_value.data, a_name.data(), IsDisplayObject());
		}

		void VisitMembers(ObjectVisitor* a_visitor) const
		{
			assert(IsObject());
			return _objectInterface->VisitMembers(_value.data, a_visitor, IsDisplayObject());
		}

		void VisitMembers(ObjectVisitFn&& a_visitor) const
		{
			assert(IsObject());

			struct MemberVisitor : ObjectInterface::ObjVisitor
			{
			public:
				MemberVisitor(ObjectVisitFn&& a_fn) :
					_fn(a_fn) {}

				void Visit(const char* a_name, const Value& a_val) override
				{
					if (_fn) {
						_fn(a_name, a_val);
					}
				}

			private:
				ObjectVisitFn _fn;
			};

			MemberVisitor visitor{ std::forward<ObjectVisitFn>(a_visitor) };
			return _objectInterface->VisitMembers(_value.data, std::addressof(visitor), IsDisplayObject());
		}

		std::uint32_t GetArraySize() const
		{
			assert(IsArray());
			return _objectInterface->GetArraySize(_value.data);
		}

		bool GetElement(std::uint32_t a_idx, Value* a_val) const
		{
			assert(IsArray());
			return _objectInterface->GetElement(_value.data, a_idx, a_val);
		}

		bool SetElement(std::uint32_t a_idx, const Value& a_val)
		{
			assert(IsArray());
			return _objectInterface->SetElement(_value.data, a_idx, a_val);
		}

		bool GetMember(stl::zstring a_name, Value* a_val) const
		{
			assert(IsObject());
			return _objectInterface->GetMember(_value.data, a_name.data(), a_val, IsDisplayObject());
		}

		bool SetMember(stl::zstring a_name, const Value& a_val)
		{
			assert(IsObject());
			return _objectInterface->SetMember(_value.data, a_name.data(), a_val, IsDisplayObject());
		}

		bool Invoke(const char* a_name, Value* a_result, const Value* a_args, std::size_t a_numArgs)
		{
			assert(IsObject());
			return _objectInterface->Invoke(_value.data, a_result, a_name, a_args, a_numArgs, IsDisplayObject());
		}

		bool Invoke(const char* a_name, Value* a_result = nullptr)
		{
			return Invoke(a_name, a_result, nullptr, 0);
		}

		template <std::size_t N>
		inline bool Invoke(const char* a_name, const std::array<Value, N>& a_args)
		{
			return Invoke(a_name, nullptr, a_args);
		}

		template <std::size_t N>
		inline bool Invoke(const char* a_name, Value* a_result, const std::array<Value, N>& a_args)
		{
			return Invoke(a_name, a_result, a_args.data(), a_args.size());
		}

		bool PushBack(const Value& a_val)
		{
			assert(IsArray());
			return _objectInterface->PushBack(_value.data, a_val);
		}

		bool RemoveElements(std::uint32_t a_idx, std::int32_t a_count = -1)
		{
			assert(IsArray());
			return _objectInterface->RemoveElements(_value.data, a_idx, a_count);
		}

		bool RemoveElement(std::uint32_t a_idx)
		{
			return RemoveElements(a_idx, 1);
		}

		bool ClearElements()
		{
			return RemoveElements(0);
		}

		bool GetDisplayInfo(DisplayInfo* a_info) const
		{
			assert(IsDisplayObject());
			return _objectInterface->GetDisplayInfo(_value.data, a_info);
		}

		[[nodiscard]] Movie* GetMovie() const
		{
			assert(_objectInterface && _objectInterface->movieRoot);
			return reinterpret_cast<Movie*>(_objectInterface->movieRoot);
		}

	private:
		void AcquireManagedValue(const Value& a_rhs)
		{
			assert(a_rhs._value.data && a_rhs._objectInterface);
			_objectInterface = a_rhs._objectInterface;
			_objectInterface->ObjectAddRef(this, _value.data);
		}

		[[nodiscard]] bool IsManagedValue() const noexcept
		{
			const auto managed = _type.all(ValueType::kManagedBit);
			assert(managed ? _objectInterface != nullptr : true);
			return managed;
		}

		void ReleaseManagedValue()
		{
			assert(_value.data && _objectInterface);
			_objectInterface->ObjectRelease(this, _value.data);
			_objectInterface = nullptr;
		}

		// members
		ObjectInterface*                      _objectInterface{ nullptr };     // 00
		REX::EnumSet<ValueType, std::int32_t> _type{ ValueType::kUndefined };  // 08
		ValueUnion                            _value{};                        // 10
		std::size_t                           _dataAux{ 0 };                   // 18
	};
	static_assert(sizeof(Value) == 0x20);

	class __declspec(novtable) alignas(0x08) FunctionHandler :
		public RefCountBase<FunctionHandler, 2>  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::Scaleform__GFx__FunctionHandler };
		static constexpr auto VTABLE{ VTABLE::Scaleform__GFx__FunctionHandler };

		struct Params
		{
		public:
			// members
			Value*        retVal;           // 00
			Movie*        movie;            // 08
			Value*        self;             // 10
			Value*        argsWithThisRef;  // 18
			Value*        args;             // 20
			std::uint32_t argCount;         // 28
			void*         userData;         // 30
		};
		static_assert(sizeof(Params) == 0x38);

		virtual ~FunctionHandler() = default;  // 00

		// add
		virtual void Call(const Params& a_params) = 0;  // 01
	};
	static_assert(sizeof(FunctionHandler) == 0x10);

	class __declspec(novtable) ExternalInterface :
		public State  // 00
	{
	public:
		ExternalInterface() :
			State(StateType::kExternalInterface)
		{}

		virtual ~ExternalInterface() = default;  // 00

		// add
		virtual void Callback(Movie* a_movieView, const char* a_methodName, const Value* a_args, std::uint32_t a_numArgs) = 0;  // 01
	};
	static_assert(sizeof(ExternalInterface) == 0x18);

	class __declspec(novtable) MultitouchInterface :
		public State  // 00
	{
	public:
		enum class MultitouchInputMode : std::int32_t
		{
			kNone = 0,
			kTouchPoint = 0x1,
			kGesture = 0x2,
			kMixed = (kTouchPoint | kGesture)
		};

		enum GestureMask : std::int32_t
		{
			kMTG_None = 0,
			kMTG_Pan = 0x1,
			kMTG_Zoom = 0x2,
			kMTG_Rotate = 0x4,
			kMTG_Swipe = 0x8
		};

		MultitouchInterface() :
			State(StateType::kMultitouchInterface)
		{}

		virtual std::uint32_t GetMaxTouchPoints() const = 0;
		virtual std::uint32_t GetSupportedGesturesMask() const = 0;
		virtual bool          SetMultitouchInputMode(MultitouchInputMode a_inputMode) = 0;
	};

	using MovieDisplayHandle = Render::DisplayHandle<Render::TreeRoot>;

	class __declspec(novtable) Movie :
		public RefCountBase<Movie, 327>,  // 00
		public StateBag                   // 10
	{
	public:
		enum class SetVarType : std::int32_t
		{
			kNormal,
			kSticky,
			kPermanent
		};

		enum class SetArrayType : std::int32_t
		{
			kInt,
			kDouble,
			kFloat,
			kString,
			kStringW,
			kValue
		};

		enum class ScaleModeType : std::int32_t
		{
			kNoScale,
			kShowAll,
			kExactFit,
			kNoBorder
		};

		enum class AlignType : std::int32_t
		{
			kCenter,
			kTopCenter,
			kBottomCenter,
			kCenterLeft,
			kCenterRight,
			kTopLeft,
			kTopRight,
			kBottomLeft,
			kBottomRight
		};

		enum HE_ReturnValueType
		{
			HE_NotHandled = 0,
			HE_Handled = 1,
			HE_NoDefaultAction = 2,
			HE_Completed = (HE_Handled | HE_NoDefaultAction)
		};

		enum class HitTestType : std::int32_t
		{
			kBounds = 0,
			kShapes = 1,
			kButtonEvents = 2,
			kShapesNoInvisible = 3
		};

		enum class ReportFlags : std::uint32_t
		{
			kNone = 0,
			kShortFileNames = 1 << 0,
			kNoCircularReferences = 1 << 1,
			kSuppressOverallStats = 1 << 2,
			kAddressesForAnonymObjsOnly = 1 << 3,
			kSuppressMovieDefsStats = 1 << 4,
			kNoEllipsis = 1 << 5
		};

		enum class MakeAllVisibleFlags : std::uint32_t
		{
			kNone = 0,
			kDontScaleDown = 1 << 0,
			kScaleUp50 = 1 << 1,
			kLeftTopToZero = 1 << 2
		};

		virtual MovieDef*                 GetMovieDef() const = 0;                                                                                                                            // 01
		virtual std::uint32_t             GetCurrentFrame() const = 0;                                                                                                                        // 02
		virtual bool                      HasLooped() const = 0;                                                                                                                              // 03
		virtual void                      GotoFrame(std::uint32_t a_frameNumber) = 0;                                                                                                         // 04
		virtual bool                      GotoLabeledFrame(const char* a_label, std::int32_t a_offset = 0) = 0;                                                                               // 05
		virtual void                      SetPlayState(PlayState a_state) = 0;                                                                                                                // 06
		virtual PlayState                 GetPlayState() const = 0;                                                                                                                           // 07
		virtual bool                      IsValid() = 0;                                                                                                                                      // 08
		virtual void                      SetVisible(bool a_visible) = 0;                                                                                                                     // 09
		virtual bool                      GetVisible() const = 0;                                                                                                                             // 0A
		virtual std::uint64_t             GetASTimerMs() const = 0;                                                                                                                           // 0B
		virtual void                      SetViewport(const Viewport& a_viewDesc) = 0;                                                                                                        // 0C
		virtual void                      GetViewport(Viewport* a_viewDesc) const = 0;                                                                                                        // 0D
		virtual void                      SetViewScaleMode(ScaleModeType) = 0;                                                                                                                // 0E
		virtual ScaleModeType             GetViewScaleMode() const = 0;                                                                                                                       // 0F
		virtual void                      SetViewAlignment(AlignType) = 0;                                                                                                                    // 10
		virtual AlignType                 GetViewAlignment() const = 0;                                                                                                                       // 11
		virtual RectF                     GetVisibleFrameRect() const = 0;                                                                                                                    // 12
		virtual RectF                     GetSafeRect() const = 0;                                                                                                                            // 13
		virtual void                      SetSafeRect(const RectF& a_rect) = 0;                                                                                                               // 14
		virtual void                      SetEdgeAAMode(Render::EdgeAAMode a_edgeAA) = 0;                                                                                                     // 15
		virtual Render::EdgeAAMode        GetEdgeAAMode() const = 0;                                                                                                                          // 16
		virtual void                      Restart(bool a_advance0 = true) = 0;                                                                                                                // 17
		virtual float                     Advance(float a_deltaT, std::uint32_t a_frameCatchUpCount = 2, bool a_capture = true) = 0;                                                          // 18
		virtual void                      Capture(bool a_onChangeOnly = true) = 0;                                                                                                            // 19
		virtual const MovieDisplayHandle& GetDisplayHandle() const = 0;                                                                                                                       // 1A
		virtual void                      SetCaptureThread(ThreadId a_captureThreadId) = 0;                                                                                                   // 1B
		virtual void                      ShutdownRendering(bool a_wait) = 0;                                                                                                                 // 1C
		virtual bool                      IsShutdownRenderingComplete() const = 0;                                                                                                            // 1D
		virtual void                      SetPause(bool a_pause) = 0;                                                                                                                         // 1E
		virtual bool                      IsPaused() const = 0;                                                                                                                               // 1F
		virtual void                      SetBackgroundColor(Render::Color a_bgColor) = 0;                                                                                                    // 20
		virtual void                      SetBackgroundAlpha(float a_alpha) = 0;                                                                                                              // 21
		virtual float                     GetBackgroundAlpha() const = 0;                                                                                                                     // 22
		virtual std::uint32_t             HandleEvent(const Event& a_event) = 0;                                                                                                              // 23
		virtual void                      GetMouseState(std::uint32_t a_mouseIndex, float* a_x, float* a_y, std::uint32_t* a_buttons) = 0;                                                    // 24
		virtual void                      NotifyMouseState(float a_x, float a_y, std::uint32_t a_buttons, std::uint32_t a_mouseIndex = 0) = 0;                                                // 25
		virtual bool                      HitTest(float a_x, float a_y, HitTestType a_testCond = HitTestType::kShapes, std::uint32_t a_controllerIdx = 0) = 0;                                // 26
		virtual void*                     GetUserData() const = 0;                                                                                                                            // 27
		virtual void                      SetUserData(void*) = 0;                                                                                                                             // 28
		virtual bool                      IsMovieFocused() const = 0;                                                                                                                         // 29
		virtual bool                      GetDirtyFlag(bool a_doReset = true) = 0;                                                                                                            // 2A
		virtual void                      SetMouseCursorCount(std::uint32_t a_num) = 0;                                                                                                       // 2B
		virtual std::uint32_t             GetMouseCursorCount() const = 0;                                                                                                                    // 2C
		virtual void                      SetControllerCount(std::uint32_t a_num) = 0;                                                                                                        // 2D
		virtual std::uint32_t             GetControllerCount() const = 0;                                                                                                                     // 2E
		virtual void                      GetStats(StatBag* a_bag, bool a_reset = true) = 0;                                                                                                  // 2F
		virtual MemoryHeap*               GetHeap() const = 0;                                                                                                                                // 30
		virtual void                      ForceCollectGarbage() = 0;                                                                                                                          // 31
		virtual void                      SuspendGC(bool a_suspend) = 0;                                                                                                                      // 32
		virtual void                      ScheduleGC() = 0;                                                                                                                                   // 33
		virtual void                      PrintObjectsReport(ReportFlags a_flags = ReportFlags::kNone, Log* a_log = nullptr, const char* a_swfName = nullptr) = 0;                            // 34
		virtual Render::PointF            TranslateToScreen(const Render::PointF& a_pt, Matrix2F* a_userMatrix = nullptr) = 0;                                                                // 36
		virtual RectF                     TranslateToScreen(const RectF& a_pt, Matrix2F* a_userMatrix = nullptr) = 0;                                                                         // 35
		virtual bool                      TranslateLocalToScreen(const char* a_pathToCharacter, const Render::PointF& a_pt, Render::PointF* a_presPt, Matrix2F* a_userMatrix = nullptr) = 0;  // 37
		virtual bool                      SetControllerFocusGroup(std::uint32_t a_controllerIdx, std::uint32_t a_focusGroupIndex) = 0;                                                        // 38
		virtual std::uint32_t             GetControllerFocusGroup(std::uint32_t a_controllerIdx) const = 0;                                                                                   // 39
		virtual void                      ResetInputFocus(std::uint32_t a_controllerIdx) = 0;                                                                                                 // 3A
		virtual bool                      IsExitRequested() const = 0;                                                                                                                        // 3B
		virtual void                      GetViewMatrix3D(Matrix3F*) = 0;                                                                                                                     // 3C
		virtual void                      SetViewMatrix3D(const Matrix3F& a_matrix) = 0;                                                                                                      // 3D
		virtual void                      GetProjectionMatrix3D(Matrix4F*) = 0;                                                                                                               // 3E
		virtual void                      SetProjectionMatrix3D(const Matrix4F& a_matrix) = 0;                                                                                                // 3F
		virtual void                      SetStageAutoOrients(bool a_value = true) = 0;                                                                                                       // 40
		virtual void                      ForceUpdateImages() = 0;                                                                                                                            // 41
		virtual void                      MakeAreaVisible(const Render::RectF& a_screenRect, const Render::RectF& a_box, MakeAllVisibleFlags a_flags = MakeAllVisibleFlags::kNone) = 0;       // 42
		virtual void                      RestoreViewport() = 0;                                                                                                                              // 43

		void CreateArray(Value* a_value);
		void CreateFunction(Value* a_value, FunctionHandler* a_function, void* a_userData = nullptr);
		void CreateObject(Value* a_value, const char* a_className = nullptr, const GFx::Value* a_args = nullptr, std::uint32_t a_numArgs = 0);
		bool GetVariable(Value* a_val, const char* a_pathToVar) const;
		bool SetVariable(const char* a_pathToVar, const Value& a_value, SetVarType a_setType = SetVarType::kSticky);
		bool Invoke(const char* a_methodName, Value* a_result, const char* a_argFmt, ...);
		bool Invoke(const char* a_methodName, Value* a_result, const Value* a_args, std::uint32_t a_numArgs);
		bool InvokeArgs(const char* a_methodName, Value* a_result, const char* a_argFmt, std::va_list a_args);

		void Release()
		{
			using func_t = decltype(&Movie::Release);
			static REL::Relocation<func_t> func{ REL::ID(2287230) };
			return func(this);
		}

		// members
		Ptr<ASMovieRootBase> asMovieRoot;  // 18
	};
	static_assert(sizeof(Movie) == 0x20);

	class __declspec(novtable) alignas(0x08) KeyboardState :
		public RefCountBase<KeyboardState, 2>  // 00
	{
	public:
		class __declspec(novtable) IListener
		{
		public:
			virtual ~IListener();  // 00

			// add
			virtual void OnKeyDown(InteractiveObject* a_movie, const EventId& a_eventID, std::int32_t a_keyMask) = 0;  // 01
			virtual void OnKeyUp(InteractiveObject* a_movie, const EventId& a_eventID, std::int32_t a_keyMask) = 0;    // 02
			virtual void Update(const EventId& a_eventID) = 0;                                                         // 03
		};
		static_assert(sizeof(IListener) == 0x08);

		// members
		std::byte pad[0x688 - 0x10];  // 10 - TODO
	};
	static_assert(sizeof(KeyboardState) == 0x688);

	class __declspec(novtable) ExternalLibPtr
	{
	public:
		ExternalLibPtr(MovieImpl* a_movieRoot) :
			owner(a_movieRoot)
		{}

		virtual ~ExternalLibPtr() = default;

		// members
		MovieImpl* owner;
	};
	static_assert(sizeof(ExternalLibPtr) == 0x10);
}
