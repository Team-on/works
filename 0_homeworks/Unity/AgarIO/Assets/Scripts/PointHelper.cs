using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class PointHelper : NetworkBehaviour {
	[SyncVar]
	public float sizeFromFood = 0.05f;

	[SyncVar]
	public Color color;

	[Server]
	public override void OnStartServer() {
			++GameHelper.foodCurr;
	}

	[Server]
	public override void OnNetworkDestroy() {
			--GameHelper.foodCurr;
	}

	void Update() {
		GetComponent<SpriteRenderer>().color = color;
	}
}
