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

	public GameObject rotateObjHor;
	public GameObject rotateObjVert;

	float rotationVert;

	void Awake() {
		rotationVert = transform.eulerAngles.x;
	}

	void Update() {
		if (axes == RotationAxes.MouseX) {
			rotateObjHor.transform.Rotate(0, Input.GetAxis("Mouse X") * sensitivityHor, 0, Space.World);
		}
		else if (axes == RotationAxes.MouseY) {
			rotationVert = Mathf.Clamp(rotationVert - Input.GetAxis("Mouse Y") * sensitivityVert, minimumVert, maximumVert);

			rotateObjVert.transform.localEulerAngles = new Vector3(
				rotationVert,
				rotateObjVert.transform.localEulerAngles.y,
				rotateObjVert.transform.localEulerAngles.z
			);
		}
		else {
			rotationVert = Mathf.Clamp(rotationVert - Input.GetAxis("Mouse Y") * sensitivityVert, minimumVert, maximumVert);

			rotateObjVert.transform.localEulerAngles = new Vector3(
				rotationVert,
				rotateObjVert.transform.localEulerAngles.y,
				rotateObjVert.transform.localEulerAngles.z
			);

			rotateObjHor.transform.localEulerAngles = new Vector3(
				rotateObjHor.transform.localEulerAngles.x,
				rotateObjHor.transform.localEulerAngles.y + Input.GetAxis("Mouse X") * sensitivityHor,
				rotateObjHor.transform.localEulerAngles.z
			);
		}
	}
}