#include <swiftly/swiftly.h>
#include <swiftly/server.h>
#include <swiftly/commands.h>
#include <swiftly/configuration.h>

Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Commands *commands = nullptr;
Configuration *config = nullptr;

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);

    server = new Server();
    g_playerManager = new PlayerManager();
    commands = new Commands(pluginName);
    config = new Configuration();
}

void Command_Resetscore(Player *player)
{
    player->stats->Set(KILLS, 0);
    player->stats->Set(DEATHS, 0);
    player->stats->Set(ASSISTS, 0);
    player->stats->Set(DAMAGE, 0);
    player->SendMsg(HUD_PRINTTALK, FetchTranslation("resetscore.resetscore.message"), config->Fetch<const char*>("resetscore.prefix"));
}

void OnPluginStart()
{
    commands->Register("resetscore", reinterpret_cast<void*>(&Command_Resetscore));
    commands->Register("rs", reinterpret_cast<void*>(&Command_Resetscore));
}

void OnPluginStop()
{

}

const char *GetPluginAuthor()
{
    return "Moongetsu";
}

const char *GetPluginVersion()
{
    return "1.0.0";
}

const char *GetPluginName()
{
    return "Swiftly Resetscore";
}

const char *GetPluginWebsite()
{
    return "";
}