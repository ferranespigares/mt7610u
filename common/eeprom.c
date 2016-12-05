/*
 *************************************************************************
 * Ralink Tech Inc.
 * 5F., No.36, Taiyuan St., Jhubei City,
 * Hsinchu County 302,
 * Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2010, Ralink Technology, Inc.
 *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the                         *
 * Free Software Foundation, Inc.,                                       *
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                       *
 *************************************************************************/


#include "rt_config.h"


INT RtmpChipOpsEepromHook(struct rtmp_adapter*pAd, INT infType)
{
	struct rtmp_chip_ops  *pChipOps = &pAd->chipOps;

#ifdef RTMP_EFUSE_SUPPORT
	efuse_probe(pAd);
	if(pAd->bUseEfuse)
	{
		pChipOps->ee_init = eFuse_init;
		pChipOps->ee_read = rtmp_ee_efuse_read16;
		pChipOps->ee_write = rtmp_ee_efuse_write16;
		DBGPRINT(RT_DEBUG_OFF, ("NVM is EFUSE\n"));
		DBGPRINT(RT_DEBUG_TRACE, ("Efuse Size=0x%x [Range:%x-%x] \n",
				pAd->chipCap.EFUSE_USAGE_MAP_SIZE,
				pAd->chipCap.EFUSE_USAGE_MAP_START,
				pAd->chipCap.EFUSE_USAGE_MAP_END));

		return 0 ;
	}
	else
	{
		pAd->bFroceEEPROMBuffer = false;
		DBGPRINT(RT_DEBUG_OFF, ("NVM is EEPROM\n"));
	}
#endif /* RTMP_EFUSE_SUPPORT */

	switch(infType)
	{


#ifdef RTMP_USB_SUPPORT
		case RTMP_DEV_INF_USB:
			pChipOps->ee_init = NULL;
			pChipOps->ee_read = RTUSBReadEEPROM16;
			pChipOps->ee_write = RTUSBWriteEEPROM16;
			DBGPRINT(RT_DEBUG_OFF, ("pChipOps->eeread = RTUSBReadEEPROM16\n"));
			DBGPRINT(RT_DEBUG_OFF, ("pChipOps->eewrite = RTUSBWriteEEPROM16\n"));
			break;
#endif /* RTMP_USB_SUPPORT */
		default:
			DBGPRINT(RT_DEBUG_ERROR, ("RtmpChipOpsEepromHook() failed!\n"));
			break;
	}

	return 0;
}

