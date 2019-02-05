using System;
using UnityEngine;
using UnityEngine.Networking;

public class NetworkPlayer : NetworkBehaviour {
	[SyncVar]
	public Color color;
	[SyncVar]
	public string playerName;

	void Start () {
	
	}
	
	void Update () {
	
	}
}
