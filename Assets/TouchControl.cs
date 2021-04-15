using UnityEngine;
using UnityEngine.UI;
using System.Collections;


// Input.GetTouch example.
//
// Attach to an origin based cube.
// A screen touch moves the cube on an iPhone or iPad.
// A second screen touch reduces the cube size.

public class TouchControl : MonoBehaviour
{
    private Vector3 position;
    private float width;
    private float height;
    public float timelimt = 1f;
     float timeLeft;

    public Text posdisplay;

    public GameObject MttQsender;
    public bool desktop;
    public string DataTOSend;

    string previousdata;

    void Awake()
    {
       // width = (float)Screen.width / 2.0f;
       // height = (float)Screen.height / 2.0f;
         height = 2f * Camera.main.orthographicSize;
         width = height * Camera.main.aspect;
        Debug.Log(width);
        Debug.Log(height);
        Camera.main.transform.position = new Vector3(width/2, height/2, -10f);

        // Position used for the cube.
        position = new Vector3(0.0f, 0.0f, 0.0f);

        if (SystemInfo.deviceType == DeviceType.Desktop)
        {
            desktop = true;
        }
    }

    

    void Update()
    {

        if (desktop)
        {
            Vector3 mouseWorldPosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            //Vector2 mouseposition2D = new Vector3(mouseWorldPosition.x, mouseWorldPosition.y);
            mouseWorldPosition.z = 0f;
            transform.position = mouseWorldPosition;

            string Data = mouseWorldPosition.x.ToString("#.00") + "," + mouseWorldPosition.y.ToString("#.00");
            //Debug.Log(Data);

            timeLeft -= Time.deltaTime;

            if (timeLeft < 0)
            {
                if (Data != previousdata)
                {
                    MttQsender.GetComponent<TestMqtt>().SendString(Data);
                    timeLeft = timelimt;                    
                    previousdata = Data;
                }
            }

        }
        else
        {

            // Handle screen touches.
            if (Input.touchCount > 0)
            {
                Touch touch = Input.GetTouch(0);
                // Debug.Log(touch.position);

                // Move the cube if the screen has the finger moving.
                if (touch.phase == TouchPhase.Moved)
                {
                    timeLeft -= Time.deltaTime;
                    if (timeLeft < 0)
                    {

                    }
                    Vector2 pos = Camera.main.ScreenToWorldPoint(touch.position);

                    Debug.Log(pos);

                    // Position the cube.
                    transform.position = pos;

                    string touchData = pos.x.ToString("#.00") + "," + pos.y.ToString("#.00");

                    if (GameObject.Find("Scenetransfer").GetComponent<SceneTransfer>().mode == "Send")
                        posdisplay.text = touchData;

                    if (timeLeft < 0)
                    {
                        if (touchData != previousdata)
                        {
                            DataTOSend = DataTOSend + touchData;
                            DataTOSend = DataTOSend + "|";
                            //MttQsender.GetComponent<TestMqtt>().SendString(touchData);
                            timeLeft = timelimt;
                            previousdata = touchData;
                        }
                    }


                }
                if(touch.phase == TouchPhase.Ended)
                {                       
                  MttQsender.GetComponent<TestMqtt>().SendString(DataTOSend);
                  DataTOSend = "";
                }
            }
        }
        
    }


}