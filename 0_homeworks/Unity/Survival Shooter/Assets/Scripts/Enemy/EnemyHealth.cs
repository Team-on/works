using UnityEngine;

public class EnemyHealth : MonoBehaviour {
	public int startingHealth = 100;            // The amount of health the enemy starts the game with.
	public int currentHealth;                   // The current health the enemy has.
	public float sinkSpeed = 2.5f;              // The speed at which the enemy sinks through the floor when dead.
	public int scoreValue = 10;                 // The amount added to the player's score when the enemy dies.
	public AudioClip deathClip;                 // The sound to play when the enemy dies.

	Animator anim;                              // Reference to the animator.
	AudioSource enemyAudio;                     // Reference to the audio source.
	ParticleSystem hitParticles;                // Reference to the particle system that plays when the enemy is damaged.
	CapsuleCollider capsuleCollider;            // Reference to the capsule collider.
	bool isDead;                                // Whether the enemy is dead.
	bool isSinking;                             // Whether the enemy has started sinking through the floor.


	void Awake() {
		anim = GetComponent<Animator>();
		enemyAudio = GetComponent<AudioSource>();
		hitParticles = GetComponentInChildren<ParticleSystem>();
		capsuleCollider = GetComponent<CapsuleCollider>();

		currentHealth = startingHealth;
	}

	void Update() {
		if (isSinking)
			transform.Translate(Vector3.down * sinkSpeed * Time.deltaTime);
	}


	public void TakeDamage(int amount, Vector3 hitPoint) {
		if (isDead)
			return;

		enemyAudio.Play();

		hitParticles.transform.position = hitPoint;
		hitParticles.Play();

		currentHealth -= amount;
		if (currentHealth <= 0) 
			Death();
	}


	void Death() {
		isDead = true;
		capsuleCollider.enabled = false;

		anim.SetTrigger("Dead");

		enemyAudio.clip = deathClip;
		enemyAudio.Play();
	}


	public void StartSinking() {
		GetComponent<UnityEngine.AI.NavMeshAgent>().enabled = false;
		GetComponent<Rigidbody>().isKinematic = true;

		isSinking = true;

		//ScoreManager.score += scoreValue;

		Destroy(gameObject, 2f);
	}
}