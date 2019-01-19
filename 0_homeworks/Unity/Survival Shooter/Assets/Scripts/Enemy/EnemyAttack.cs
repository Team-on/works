using UnityEngine;

public class EnemyAttack : MonoBehaviour {
	public float timeBetweenAttacks = 0.5f;     // The time in seconds between each attack.
	public int attackDamage = 10;               // The amount of health taken away per attack.


	Animator anim;                              // Reference to the animator component.
	GameObject player;                          // Reference to the player GameObject.
	PlayerHealth playerHealth;                  // Reference to the player's health.
	//EnemyHealth enemyHealth;                    // Reference to this enemy's health.
	bool playerInRange;                         // Whether player is within the trigger collider and can be attacked.
	float timer;                                // Timer for counting up to the next attack.


	void Awake() {
		player = GameObject.FindGameObjectWithTag("Player");
		playerHealth = player.GetComponent<PlayerHealth>();
		//enemyHealth = GetComponent<EnemyHealth>();
		anim = GetComponent<Animator>();
	}


	void OnTriggerEnter(Collider other) {
		if (other.gameObject == player)
			playerInRange = true;
	}


	void OnTriggerExit(Collider other) {
		if (other.gameObject == player)
			playerInRange = false;
	}


	void Update() {
		timer += Time.deltaTime;

		if (timer >= timeBetweenAttacks && playerInRange /*&& enemyHealth.currentHealth > 0*/) 
			Attack();

		if (playerHealth.currentHealth <= 0) 
			anim.SetTrigger("PlayerDead");
	}


	void Attack() {
		timer = 0f;

		if (playerHealth.currentHealth > 0) 
			playerHealth.TakeDamage(attackDamage);
	}
}