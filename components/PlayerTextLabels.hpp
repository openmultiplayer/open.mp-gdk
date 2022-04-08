#pragma once
#include "../main.hpp"

namespace ompgdk
{
    inline int CreatePlayer3DTextLabel(int playerid, const char* text, uint32_t colour, float x, float y, float z, float drawDistance, int attachedPlayerId, int attachedVehicleId, bool los)
    {
        IPlayerTextLabelData* labelData = GetPlayerData<IPlayerTextLabelData>(playerid);
        if (labelData) 
        {
            IPlayerTextLabel* textlabel = nullptr;

            IPlayer* attachedPlayer = GetPlayer(attachedPlayerId);
            IVehicle* attachedVehicle = GetEntity<IVehicle>(attachedVehicleId);

            if (attachedPlayer)
            {
                textlabel = labelData->create(text, Colour::FromRGBA(colour), { x, y ,z }, drawDistance, los, *attachedPlayer);
            }
            else if (attachedVehicle) 
            {
                textlabel = labelData->create(text, Colour::FromRGBA(colour), { x, y ,z }, drawDistance, los, *attachedVehicle);
            }
            else
            {
                textlabel = labelData->create(text, Colour::FromRGBA(colour), { x, y ,z }, drawDistance, los);
            }

            if (textlabel) 
            {
                return textlabel->getID();
            }
        }
        return INVALID_TEXT_LABEL_ID;
    }

    inline bool DeletePlayer3DTextLabel(int playerid, int textlabelid)
    {
        IPlayerTextLabelData* labelData = GetPlayerData<IPlayerTextLabelData>(playerid);
        if (labelData->get(textlabelid))
        {
            labelData->release(textlabelid);
            return true;
        }
        return false;
    }

    inline bool UpdatePlayer3DTextLabelText(int playerid, int textlabelid, uint32_t colour, const char* text)
    {
        GET_PLAYER_TEXT_LABEL_CHECKED(textlabel, playerid, textlabelid, false);
        textlabel->setColour(Colour::FromRGBA(colour));
        textlabel->setText(text);
        return true;
    }

    inline bool IsValidPlayer3DTextLabel(int playerid, int textlabelid)
    {
        GET_PLAYER_TEXT_LABEL_CHECKED(textlabel, playerid, textlabelid, false);
        return true;
    }

    inline bool GetPlayer3DTextLabelText(int playerid, int textlabelid, char* output, int size)
    {
        GET_PLAYER_TEXT_LABEL_CHECKED(textlabel, playerid, textlabelid, false);
        output = const_cast<char*>(textlabel->getText().data());
        output[size - 1] = '\0';
        return true;
    }

    inline uint32_t GetPlayer3DTextLabelColor(int playerid, int textlabelid)
    {
        GET_PLAYER_TEXT_LABEL_CHECKED(textlabel, playerid, textlabelid, 0);
        return textlabel->getColour().RGBA();
    }

    inline bool GetPlayer3DTextLabelPos(int playerid, int textlabelid, float* out_x, float* out_y, float* out_z)
    {
        GET_PLAYER_TEXT_LABEL_CHECKED(textlabel, playerid, textlabelid, false);
        Vector3 out = textlabel->getPosition();
        *out_x = out.x;
        *out_y = out.y;
        *out_z = out.z;
        return true;
    }

    inline bool SetPlayer3DTextLabelDrawDist(int playerid, int textlabelid, float distance)
    {
        GET_PLAYER_TEXT_LABEL_CHECKED(textlabel, playerid, textlabelid, false);
        textlabel->setDrawDistance(distance);
        return true;
    }

    inline float GetPlayer3DTextLabelDrawDist(int playerid, int textlabelid)
    {
        GET_PLAYER_TEXT_LABEL_CHECKED(textlabel, playerid, textlabelid, 0.0f);
        return textlabel->getDrawDistance();
    }

    inline bool GetPlayer3DTextLabelLOS(int playerid, int textlabelid)
    {
        GET_PLAYER_TEXT_LABEL_CHECKED(textlabel, playerid, textlabelid, false);
        return textlabel->getTestLOS();
    }

    inline bool SetPlayer3DTextLabelLOS(int playerid, int textlabelid, bool status)
    {
        GET_PLAYER_TEXT_LABEL_CHECKED(textlabel, playerid, textlabelid, false);
        textlabel->setTestLOS(status);
        return true;
    }

    inline int GetPlayer3DTextLabelVirtualW(int playerid, int textlabelid)
    {
        // No virtual world support, returning player virtual world.
        GET_PLAYER_CHECKED(player, playerid, 0);
        return player->getVirtualWorld();
    }

    inline bool GetPlayer3DTextLabelAttached(int playerid, int textlabelid, int* attached_player, int* attached_vehicle)
    {
        GET_PLAYER_TEXT_LABEL_CHECKED(textlabel, playerid, textlabelid, false);
        const TextLabelAttachmentData& data = textlabel->getAttachmentData();

        *attached_player = data.playerID;
        *attached_vehicle = data.vehicleID;
        return true;
    }
}
