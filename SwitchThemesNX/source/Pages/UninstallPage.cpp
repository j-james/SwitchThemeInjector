#include "UninstallPage.hpp"
#include "../ViewFunctions.hpp"
#include "../SwitchTools/PatchMng.hpp"

using namespace std;

UninstallPage::UninstallPage()
{
	Name = "Uninstall theme";
}

void UninstallPage::Render(int X, int Y)
{
	Utils::ImGuiSetupPage(this, X, Y);
	ImGui::PushFont(font30);

	ImGui::TextWrapped("Use this to uninstall the currently installed themes.\nIf you have issues, try fully removing the LayeredFS directory and home menu patches by pressing L+R as well.");

	ImGui::PushStyleColor(ImGuiCol_Button, u32(0x6B70000ff));
	if (ImGui::Button("Uninstall"))
	{
		bool FullUninstall = gamepad.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER] && gamepad.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER];
		PushFunction([FullUninstall]() {
			if (!YesNoPage::Ask("Are you sure ?")) return;
			if (FullUninstall)
			{
				DisplayLoading("Clearing LayeredFS dir...");
				fs::theme::UninstallTheme(true);
				PatchMng::RemoveAll();
				Dialog(
					"Done, everything theme-related has been removed, restart your console to see the changes.\n"
					"As this removed the home menu patches as well you should restart this homebrew before installing any theme."
				);
			}
			else
			{
				DisplayLoading("Loading...");
				fs::theme::UninstallTheme(false);
				Dialog("Done, all the installed themes have been removed, restart your console to see the changes");
			}
		});
	}
	PAGE_RESET_FOCUS;
	ImGui::PopStyleColor();

	ImGui::PopFont();
	Utils::ImGuiSetWindowScrollable();
	Utils::ImGuiCloseWin();
}

void UninstallPage::Update()
{	
	if (Utils::PageLeaveFocusInput()){
		Parent->PageLeaveFocus(this);
	}
}




