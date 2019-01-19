using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class PlayerHealth : MonoBehaviour {
	public int startingHealth = 100;                            // The amount of health the player starts the game with.
	public int currentHealth;                                   // The current health the player has.
	public Slider healthSlider;                                 // Reference to the UI's health bar.
	public Image damageImage;                                   // Reference to an image to flash on the screen on being hurt.
	public AudioClip deathClip;                                 // The audio clip to play when the player dies.
	public float flashSpeed = 5f;                               // The speed the damageImage will fade at.
	public Color flashColour = new Color(1f, 0f, 0f, 0.1f);     // The colour the damageImage is set to, to flash.


	Animator anim;                                              // Reference to the Animator component.
	AudioSource playerAudio;                                    // Reference to the AudioSource component.
	PlayerMovement playerMovement;                              // Reference to the player's movement.
	PlayerShooting playerShooting;                              // Reference to the PlayerShooting script.
	bool isDead;                                                // Whether the player is dead.
	bool damaged;                                               // True when the player gets damaged.


	void Awake() {
		anim = GetComponent<Animator>();
		playerAudio = GetComponent<AudioSource>();
		playerMovement = GetComponent<PlayerMovement>();
		playerShooting = GetComponentInChildren<PlayerShooting>();

		currentHealth = startingHealth;
	}


	void Update() {
		damageImage.color = damaged ? flashColour : Color.Lerp(damageImage.color, Color.clear, flashSpeed * Time.deltaTime);
		damaged = false;
	}


	public void TakeDamage(int amount) {
		damaged = true;
		currentHealth -= amount;
		healthSlider.value = currentHealth;
		playerAudio.Play();

		if (currentHealth <= 0 && !isDead) 
			Death();
	}


	void Death() {
		isDead = true;
		playerShooting.DisableEffects();
		playerMovement.enabled = false;
		playerShooting.enabled = false;

		anim.SetTrigger("Die");

		playerAudio.clip = deathClip;
		playerAudio.Play();
	}
}