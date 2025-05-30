#pragma once

namespace RE
{
	enum class DIALOGUE_SUBTYPE : std::int32_t
	{
		kPlayerDialogue_Custom = 0x0,
		kPlayerDialogue_Force_Greet = 0x1,
		kPlayerDialogue_Player_Rumor = 0x2,
		kPlayerDialogue_End = 0x3,
		kCommandDialogue_Custom = 0x3,
		kCommandDialogue_Call = 0x4,
		kCommandDialogue_Follow = 0x5,
		kCommandDialogue_Move = 0x6,
		kCommandDialogue_Attack = 0x7,
		kCommandDialogue_Inspect = 0x8,
		kCommandDialogue_Retrieve = 0x9,
		kCommandDialogue_Stay = 0xA,
		kCommandDialogue_Release = 0xB,
		kCommandDialogue_ShowRelationships = 0xC,
		kCommandDialogue_Reject = 0xD,
		kCommandDialogue_Heal = 0xE,
		kCommandDialogue_Assign = 0xF,
		kCommandDialogue_Enter = 0x10,
		kSceneDialogue_Custom = 0x11,
		kFavor_Show = 0x12,
		kFavor_Agree = 0x13,
		kFavor_Refuse = 0x14,
		kFavor_Exit_State = 0x15,
		kFavor_Morality_Refuse = 0x16,
		kFavor_Trade = 0x17,
		kFavor_Pathing_Reject = 0x18,
		kCombat_Attack = 0x19,
		kCombat_Power_Attack = 0x1A,
		kCombat_Bash = 0x1B,
		kCombat_Hit = 0x1C,
		kCombat_Flee = 0x1D,
		kCombat_Bleed_Out = 0x1E,
		kCombat_Avoid_Threat = 0x1F,
		kCombat_Death = 0x20,
		kCombat_Block = 0x21,
		kCombat_Taunt = 0x22,
		kCombat_Throw_Grenade = 0x23,
		kCombat_Ally_Killed = 0x24,
		kCombat_Order_Fallback = 0x25,
		kCombat_Order_Advance = 0x26,
		kCombat_Order_Flank = 0x27,
		kCombat_Order_Take_Cover = 0x28,
		kCombat_Fallback = 0x29,
		kCombat_Request_Support = 0x2A,
		kCombat_Provide_Support = 0x2B,
		kCombat_Crippled_Limb = 0x2C,
		kCombat_Paired_Attack = 0x2D,
		kCombat_Steal = 0x2E,
		kCombat_Yield = 0x2F,
		kCombat_Accept_Yield = 0x30,
		kCombat_Pickpocket = 0x31,
		kCombat_Assault = 0x32,
		kCombat_Murder = 0x33,
		kCombat_Assault_NC = 0x34,
		kCombat_Murder_NC = 0x35,
		kCombat_Pickpocket_NC = 0x36,
		kCombat_Steal_NC = 0x37,
		kCombat_Trespass_NC = 0x38,
		kCombat_Guard_Trespass = 0x39,
		kCombat_Unused = 0x3A,
		kCombat_Voice_Power_Start = 0x3B,
		kCombat_Voice_Power_Start_Short = 0x3B,
		kCombat_Voice_Power_Start_Long = 0x3C,
		kCombat_Voice_Power_End_Short = 0x3D,
		kCombat_Voice_Power_End_Long = 0x3E,
		kCombat_Voice_Power_End = 0x3E,
		kDetection_Alert_Idle = 0x3F,
		kDetection_Lost_Idle = 0x40,
		kDetection_Normal_To_Alert = 0x41,
		kDetection_Normal_To_Combat = 0x42,
		kDetection_Normal_To_Lost = 0x43,
		kDetection_Alert_To_Normal = 0x44,
		kDetection_Alert_To_Combat = 0x45,
		kDetection_Combat_To_Normal = 0x46,
		kDetection_Combat_To_Lost = 0x47,
		kDetection_Lost_To_Normal = 0x48,
		kDetection_Lost_To_Combat = 0x49,
		kDetection_Detect_Friend_Die = 0x4A,
		kService_Refusal = 0x4B,
		kService_Repair = 0x4C,
		kService_Travel = 0x4D,
		kService_Training = 0x4E,
		kService_Barter_Exit = 0x4F,
		kService_Repair_Exit = 0x50,
		kService_Recharge = 0x51,
		kService_Recharge_Exit = 0x52,
		kService_Training_Exit = 0x53,
		kMisc_Observe_Combat = 0x54,
		kMisc_Corpse = 0x55,
		kMisc_Time_To_Go = 0x56,
		kMisc_Goodbye = 0x57,
		kMisc_Hello = 0x58,
		kMisc_Player_Action_Swing_Melee_Weapon = 0x59,
		kMisc_Player_Action_Shoot_Bow = 0x5A,
		kMisc_Player_Action_Z_Key_Object = 0x5B,
		kMisc_Player_Action_Jumping = 0x5C,
		kMisc_Player_Action_Knocking_Over_Objects = 0x5D,
		kMisc_Player_Action_Destroy_Object = 0x5E,
		kMisc_Player_Action_Stand_On_Furniture = 0x5F,
		kMisc_Player_Action_Locked_Object = 0x60,
		kMisc_Player_Action_Pickpocket = 0x61,
		kMisc_Pursue_Idle = 0x62,
		kMisc_InfoData = 0x63,
		kMisc_SceneChoice = 0x64,
		kMisc_Player_Action_Cast_Projectile_Spell = 0x65,
		kMisc_Player_Action_Cast_Self_Spell = 0x66,
		kMisc_Player_Action_Shout = 0x67,
		kMisc_Idle = 0x68,
		kMisc_Breath_Sprint_Sound = 0x69,
		kMisc_Breath_Enter_Bow_Zoom_Sound = 0x6A,
		kMisc_Breath_Exit_Bow_Zoom_Sound = 0x6B,
		kMisc_Actor_Collide_With_Actor = 0x6C,
		kMisc_Player_Iron_Sights = 0x6D,
		kMisc_Out_Off_Breath_Sound = 0x6E,
		kMisc_Combat_Grunt = 0x6F,
		kMisc_Breath_Leave_Water = 0x70,
		kMisc_Impatient_Positive = 0x71,
		kMisc_Impatient_Negative = 0x72,
		kMisc_Impatient_Neutral = 0x73,
		kMisc_Impatient_Question = 0x74,
		kMisc_Waiting_Player_Input = 0x75,
		kMisc_Greeting = 0x76,
		kMisc_Player_Activate_Door = 0x77,
		kMisc_Player_Activate_Terminals = 0x78,
		kMisc_Player_Activate_Furniture = 0x79,
		kMisc_Player_Activate_Activators = 0x7A,
		kMisc_Player_Activate_Container = 0x7B,
		kMisc_Player_Aquire_Featured_Item = 0x7C,
	};
}
