using UnityEngine;

public class EnemyManager : MonoBehaviour {
	public PlayerHealth playerHealth;       // Reference to the player's heatlh.
	public float spawnTime = 3f;            // How long between each spawn.
	public GameObject[] enemies;                // The enemy prefab to be spawned.
	public Transform[] spawnPoints;         // An array of the spawn points this enemy can spawn from.


	void Start() {
		InvokeRepeating("Spawn", spawnTime, spawnTime);
	}


	void Spawn() {
		if (playerHealth.currentHealth <= 0)
			return;

		int spawnPointIndex = Random.Range(0, spawnPoints.Length);
		int enamyIndex = Random.Range(0, enemies.Length);
		Instantiate(enemies[enamyIndex], spawnPoints[spawnPointIndex].position, spawnPoints[spawnPointIndex].rotation);
	}
}