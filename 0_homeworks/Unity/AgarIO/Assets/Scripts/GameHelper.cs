using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class GameHelper : NetworkBehaviour {
	public GameObject foodPrefab;
	
	internal PlayerHelper playerHelper;

	[Server]
	void Start () {
		for (int i = 0; i < 10; i++) {
			GameObject point = Instantiate(foodPrefab);
			point.transform.position = Random.insideUnitCircle * Random.Range(5, 10);
			NetworkServer.Spawn(point);
		}
	}
	
	void Update () {
		
	}
}
