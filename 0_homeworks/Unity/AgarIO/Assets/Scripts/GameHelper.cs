using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class GameHelper : NetworkBehaviour {
	public static int foodMax = 100;
	public static int foodCurr = 0;

	public Vector2 mapSize = new Vector2(20, 20);
	public GameObject foodPrefab;
	
	internal PlayerHelper playerHelper;

	[Server]
	void Start () {
		for (int i = 0; i < foodMax; i++)
			CreateFood();
	}

	[Server]
	void Update () {
		if(foodCurr < foodMax)
			CreateFood();
	}

	[Server]
	private void CreateFood() {
		GameObject point = Instantiate(foodPrefab);
		point.transform.position = new Vector2(Random.Range(-mapSize.x, mapSize.x), Random.Range(-mapSize.y, mapSize.y));
		NetworkServer.Spawn(point);
		++foodCurr;
	}
}
