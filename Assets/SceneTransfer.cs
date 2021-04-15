using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneTransfer : MonoBehaviour
{
    public static SceneTransfer instance;
    public string mode;

    void Awake()
    {
        // Application.targetFrameRate = 60;

        if (instance == null)
            instance = this;
        else
        {
            Destroy(gameObject);
            return;
        }

        DontDestroyOnLoad(gameObject);        
    }



    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void gotosenderscene()
    {
        mode = "Send";
        SceneManager.LoadScene("Scene");
    }
    

    public void gotoreceivescene()
    {
        mode = "Receive";
        SceneManager.LoadScene("Scene");
    }

    
}
