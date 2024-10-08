//
// Created by admin on 2024/7/28.
//

#include "economyAPI.h"

ENDSTONE_PLUGIN("economy_api", "0.1.0", economyAPI)
{
    description = "Economy for minecraftBE";
    command("economy")
            .description("Economy System")
            .usages("/economy (show|top|pay|add|reduce|set)<parameter:enum> [playerName:player] [money:int]")
            .permissions("economy.use.base");

    permission("economy.use.base")
    /*
     * children(true是继承parent权限范围 false是反转)
     */
            .description("Allow users to use the /economy command.")
            .default_(endstone::PermissionDefault::True)
            .children("economy.command.show", true)
            .children("economy.command.pay", true)
            .children("economy.command.add", false)
            .children("economy.command.reduce", false)
            .children("economy.command.set", false)
            .children("economy.command.show.others", false)
            .children("economy.command.top", true);
}




