using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PointHelper : MonoBehaviour {
	public float sizeFromFood = 0.05f;

	void OnDestroy() {
		--GameHelper.foodCurr;
	}
}
