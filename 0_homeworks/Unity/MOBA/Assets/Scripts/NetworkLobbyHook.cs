using System.Collections;
using UnityEngine;
using UnityEngine.Networking;
using UnityStandardAssets.Network;

public class NetworkLobbyHook : LobbyHook {
	public override void OnLobbyServerSceneLoadedForPlayer(NetworkManager manager, GameObject lobbyPlayer, GameObject gamePlayer) {
		LobbyPlayer lobby = lobbyPlayer.GetComponent<LobbyPlayer>();
		NetworkPlayer hero = gamePlayer.GetComponent<NetworkPlayer>();

		hero.playerName = lobby.name;
		hero.color = lobby.playerColor;
	}
}
