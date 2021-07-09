#include "hud.h"
#include "cl_util.h"
#include "parsemsg.h"
#include "update_checker.h"

int CHudWatermark::Init()
{
	m_iFlags = 0;

	gHUD.AddHudElem(this);
	return 0;
}

int CHudWatermark::VidInit()
{
	m_iFlags |= HUD_ACTIVE;
	refresh_draw_until = true;
	update_is_available = update_checker::is_update_available();

	return 1;
}

int CHudWatermark::Draw(float time)
{
	if (refresh_draw_until) {
		refresh_draw_until = false;
		draw_until = gHUD.m_flTime + 15.0f;
	}

	if (gHUD.m_flTime >= draw_until) {
		m_iFlags &= ~HUD_ACTIVE;
		return 0;
	}

	int r, g, b;
	UnpackRGB(r, g, b, gHUD.m_iDefaultHUDColor);

	gEngfuncs.pfnDrawString(ScreenWidth / 20, gHUD.m_scrinfo.iCharHeight, "Aura client build "  __TIMESTAMP__, r, g, b);
	gEngfuncs.pfnDrawString(ScreenWidth / 20, gHUD.m_scrinfo.iCharHeight * 2, "Half-Life: Zombies Ate My Neighbours Multiplayer 2.6-PPT2", r, g, b);
	gEngfuncs.pfnDrawString(ScreenWidth / 20, gHUD.m_scrinfo.iCharHeight * 3, "Season 6: HECU", r, g, b);

	if (update_is_available)
		gEngfuncs.pfnDrawString(ScreenWidth / 20, gHUD.m_scrinfo.iCharHeight / 2 * 7, " ", r, g, b);

	return 0;
}
