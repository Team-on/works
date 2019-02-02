using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PointHelper : UnityEngine.Networking.NetworkBehaviour {
	public float sizeFromFood = 0.05f;

	public override void OnStartServer() {
		if(isServer)
			++GameHelper.foodCurr;
	}

	public override void OnNetworkDestroy() {
		if(isServer)
			--GameHelper.foodCurr;
	}
}
