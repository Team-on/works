using UnityEngine;
using UnityEngine.Networking;

public class PlayerHelper : NetworkBehaviour {
	GameHelper localGameHelper;
	NetworkIdentity ni;

	void Start() {
		ni = GetComponent<NetworkIdentity>();
		localGameHelper = FindObjectOfType<GameHelper>();

		if (isLocalPlayer)
			localGameHelper.localPlayerHelper = this;
	}

	public void Send(string message) {
		CmdSend(ni.netId.Value.ToString(), message);
	}

	[Command]
	void CmdSend(string id, string message) {
		RpcSend(id, message);
		
		if (message == "/random")
			RpcSend("Server", Random.Range(0, 21).ToString());
	}

	[ClientRpc]
	void RpcSend(string id, string message) {
		localGameHelper.text.text += id + ": " + message + System.Environment.NewLine;
	}

	void Update() {

	}
}
