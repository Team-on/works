using System.Collections;
using System.Collections.Generic;
using UnityEngine.Networking;

public class PointHelper : NetworkBehaviour {
	public float sizeFromFood = 0.05f;

	[Server]
	public override void OnStartServer() {
			++GameHelper.foodCurr;
	}

	[Server]
	public override void OnNetworkDestroy() {
			--GameHelper.foodCurr;
	}
}
