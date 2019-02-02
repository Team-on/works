using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MouseLook : MonoBehaviour {
	public enum RotationAxes { MouseXAndY, MouseX, MouseY }

	public RotationAxes axes = RotationAxes.MouseXAndY;

	public float sensitivityHor = 9f;

	public float sensitivityVert = 9.0f;
	public float minimumVert = -45.0f;
	public float maximumVert = 45.0f;

	float rotationVert;

	void Start() {
		rotationVert = transform.eulerAngles.x;
	}

	void Update() {
		if (axes == RotationAxes.MouseX) {
			transform.Rotate(0, Input.GetAxis("Mouse X") * sensitivityHor, 0, Space.World);
		}
		else if (axes == RotationAxes.MouseY) {
			rotationVert = Mathf.Clamp(rotationVert - Input.GetAxis("Mouse Y") * sensitivityVert, minimumVert, maximumVert);

			transform.localEulerAngles = new Vector3(
				rotationVert,
				transform.localEulerAngles.y,
				transform.localEulerAngles.z
			);
		}
		else {
			rotationVert = Mathf.Clamp(rotationVert - Input.GetAxis("Mouse Y") * sensitivityVert, minimumVert, maximumVert);

			transform.localEulerAngles = new Vector3(
				rotationVert,
				transform.localEulerAngles.y + Input.GetAxis("Mouse X") * sensitivityHor,
				transform.localEulerAngles.z
			);

		}
	}
}