using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
  bool gameEnded = false;
  public float restartDelay = 1f;
  public GameObject completeLevelIU;

  public void CompleteLevel()
  {
    completeLevelIU.SetActive(true);
  }
  public void EndGame()
  {
    if (!gameEnded)
    {
      this.gameEnded = true;
      Invoke("RestartGame", restartDelay);
    }
  }

  public void RestartGame()
  {
    SceneManager.LoadScene(SceneManager.GetActiveScene().name);
  }
}
