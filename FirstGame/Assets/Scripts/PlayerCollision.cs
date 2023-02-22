using UnityEngine;

public class PlayerCollision : MonoBehaviour
{
  public PlayerMovement movement;
  void OnCollisionEnter(Collision colission)
  {
    System.Diagnostics.Debug.Assert(condition: colission.collider != null, "GameObject is null");
    if (colission.collider.tag == "Obstacle")
    {
      /** 
       * By using "GetComponent and FindObjectOfType we can avoid using a variable on the class.
       * That way, if the player is removed from the scene, this script will be able to find another instance of
       * a player. However, this is not a direct reference to the object, so be carefeul with that.
       */
      GetComponent<PlayerMovement>().StopPlayer();
      FindObjectOfType<GameManager>().EndGame();
    }
  }
}
