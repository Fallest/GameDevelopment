using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
  public Rigidbody playerBody;
  public bool playerCanMove = true;
  public float forwardForce = 500f;
  public float sideForce = 1000f;
  public float jumpForce = 2f;
  public Vector3 startPos = new Vector3(0, 0, 0);
  public Vector3 stopVec = new Vector3(0, 0, 0);

  // Start is called before the first frame update
  //void Start() {
  //  playerBody.AddForce(0, 200, 500);
  //}

  /** 
   * Stop player movement and avoid any more movement.
   */
  public void StopPlayer()
  {
    this.playerBody.velocity = stopVec;
    this.playerCanMove = false;
  }

  /** 
   * Move the player back to the start, reset its transform.
   */
  public void RestartGame()
  {
    this.playerBody.MovePosition(position: startPos);
    this.playerBody.transform.rotation = new Quaternion(0, 0, 0, 0);
    this.playerBody.velocity = stopVec;
    this.playerCanMove = true;
  }

  // FixedUpdate is called once per frame (for physics updates, for everything else use Update)
  void FixedUpdate()
  {
    // Reset player position and speed
    if (Input.GetKey("r") || playerBody.position.y < -1f)
    {
      FindObjectOfType<GameManager>().RestartGame();
    }

    // Stride
    if (!playerCanMove) return;

    // Time.deltaTime is the amount of seconds since the last time the computer drew the last frame.
    // The higher the framerate, the lower deltaTime will be, so it will counter high framerates.
    playerBody.AddForce(0, 0, forwardForce * Time.deltaTime);

    if (Input.GetKey("d"))
    {
      playerBody.AddForce(sideForce * Time.deltaTime, 0, 0, ForceMode.VelocityChange);
    }
    if (Input.GetKey("a"))
    {
      playerBody.AddForce(-(sideForce * Time.deltaTime), 0, 0, ForceMode.VelocityChange);
    }

    // Jump
    if (Input.GetKey("space") && playerBody.position.y < 1)
    {
      playerBody.MovePosition(new Vector3(playerBody.position.x, jumpForce, playerBody.position.z));
    }

  }
}
