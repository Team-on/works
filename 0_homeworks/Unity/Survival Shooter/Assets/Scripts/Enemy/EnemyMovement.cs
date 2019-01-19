using UnityEngine;
using UnityEngine.AI;

public class EnemyMovement : MonoBehaviour {
	Transform player;               // Reference to the player's position.
	PlayerHealth playerHealth;      // Reference to the player's health.
	EnemyHealth enemyHealth;        // Reference to this enemy's health.
	NavMeshAgent nav;               // Reference to the nav mesh agent.


	void Awake() {
		player = GameObject.FindGameObjectWithTag("Player").transform;
		playerHealth = player.GetComponent<PlayerHealth>();
		enemyHealth = GetComponent<EnemyHealth>();
		nav = GetComponent<NavMeshAgent>();
	}


	void Update() {
		if (enemyHealth.currentHealth > 0 && playerHealth.currentHealth > 0) 
			nav.SetDestination(player.position);
		else 
			nav.enabled = false;
	}
}