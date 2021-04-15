using UnityEngine;
using System.Collections;
using System.IO.Ports;
using System.Threading;

public class SendingAudrino : MonoBehaviour
{



    //public static SerialPort sp = new SerialPort("COM4", 9600, Parity.None, 8, StopBits.One);
    //public static SerialPort sp = new SerialPort("COM3", 9600);
    public static SerialPort sp = new SerialPort("COM5", 9600);
    //public static SerialPort sp = new SerialPort("COM4", 19200);
    //public string message2;
    //float timePassed = 0.0f;
    // Use this for initialization
    void Start()
    {
        OpenConnection();
    }

    // Update is called once per frame
    void Update()
    {
        //timePassed+=Time.deltaTime;
        //if(timePassed>=0.2f){

        //print("BytesToRead" +sp.BytesToRead);
        //message2 = sp.ReadLine();
        //print(message2);
        //	timePassed = 0.0f;
        //}
    }

    public void OpenConnection()
    {
        if (sp != null)
        {
            if (sp.IsOpen)
            {
                sp.Close();
                print("Closing port, because it was already open!");
            }
            else
            {
                sp.Open();  // opens the connection
                //InvokeRepeating("serial_Data_writing", 0f, 0.01f);

                //sp.ReadTimeout = 16;  // sets the timeout value before reporting error
                //sp.WriteTimeout(GetComponent;set ;
                print("Port Opened!");
                //		message = "Port Opened!";
            }
        }
        else
        {
            if (sp.IsOpen)
            {
                print("Port is already open");
            }
            else
            {
                print("Port == null");
            }
        }
    }

    void OnApplicationQuit()
    {
        sp.Close();
    }

   

    public static void sendmessage(string data)
    {
        // OpenConnection();
        //sendmessage(s);
        sp.Write(data);
        sp.BaseStream.Flush();
        Debug.Log(",essage sent to audrino: "+ data);
    }

    
}
