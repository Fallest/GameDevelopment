using UnityEngine;

public class Credits : MonoBehaviour
{
  public void OnQuitClick()
  {
    Debug.Log("Game quit");
    Application.Quit();
  }
}
