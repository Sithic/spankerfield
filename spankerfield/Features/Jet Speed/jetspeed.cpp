#include "jetspeed.h"
#include "../../settings.h"
#include "../../Utilities/other.h"

using namespace big;
namespace plugins
{
	void set_jet_speed()
	{
		if (!g_settings.jet_speed) return;

		const auto border_input_node = BorderInputNode::GetInstance();
		if (!border_input_node) return;

		const auto game_context = ClientGameContext::GetInstance();
		if (!game_context) return;

		const auto level = game_context->m_pLevel;
		if (!level) return;

		const auto game_world = level->m_pGameWorld;
		if (!game_world) return;

		const auto player_manager = game_context->m_pPlayerManager;
		if (!player_manager) return;

		const auto local_player = player_manager->m_pLocalPlayer;
		if (!local_player) return;

		const auto local_soldier = local_player->GetSoldier();
		if (!local_soldier) return;

		if (!local_soldier->IsAlive()) return;

		const auto local_vehicle = local_player->GetVehicle();
		if (!local_vehicle) return;

		const auto vehicle_data = get_vehicle_data(local_vehicle);
		if (!vehicle_data) return;

		if (vehicle_data->IsInJet())
		{
			const auto keyboard = border_input_node->m_pKeyboard;
			if (!keyboard) return;

			static bool key_press = false;
			if (keyboard->m_pDevice->m_Buffer[InputDeviceKeys::IDK_ArrowUp] || keyboard->m_pDevice->m_Buffer[InputDeviceKeys::IDK_ArrowDown])
			{
				auto vehicle_velocity = local_soldier->GetVelocity();
				auto velocity = sqrt(pow(vehicle_velocity->x, 2) + pow(vehicle_velocity->y, 2) + pow(vehicle_velocity->z, 2)) * 3.6f;

				if (velocity > 315.0f)
				{
					keyboard->m_pDevice->m_Buffer[InputDeviceKeys::IDK_S] = 1;
					keyboard->m_pDevice->m_Buffer[InputDeviceKeys::IDK_LeftShift] = 0;
				}
				else if (velocity < 310.0f)
				{
					keyboard->m_pDevice->m_Buffer[InputDeviceKeys::IDK_S] = 0;
					keyboard->m_pDevice->m_Buffer[InputDeviceKeys::IDK_LeftShift] = 1;
				}

				key_press = true;
			}
			else if (key_press)
			{
				keyboard->m_pDevice->m_Buffer[InputDeviceKeys::IDK_S] = 0;
				keyboard->m_pDevice->m_Buffer[InputDeviceKeys::IDK_LeftShift] = 0;
				
				key_press = false;
			}
		}
	}
}