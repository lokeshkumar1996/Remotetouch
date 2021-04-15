using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using uPLibrary.Networking.M2Mqtt;
using System;
using System.Runtime.InteropServices;
using System.Text;
using uPLibrary.Networking.M2Mqtt.Messages;
using UnityEngine.UI;

public class TestMqtt : MonoBehaviour
{
    private MqttClient4Unity client;
    private string brokerHostname = "broker.hivemq.com";
    private int brokerPort = 1883;
    private string userName = null;
    private string password = null;
    private string topic = "loky1234";
    //public String Message;
    private String PrevMsg;
    private Queue msgq = new Queue();

    private bool send;

    public Text position;

    public GameObject sendaudrino;
    public GameObject positiondisplay;

    public string oldmessage;

    private void Start()
    {
        if (brokerHostname != null)
        {
            Connect();
            client.Subscribe(topic);
        }

        if (GameObject.Find("Scenetransfer").GetComponent<SceneTransfer>().mode == "Send")
        {
            send = true;
            positiondisplay.SetActive(false);
        }
        else
        {
            send = false;
            positiondisplay.SetActive(true);
            //sendaudrino.SetActive(true);
        }
    }


    public void Connect()
    {
        client = new MqttClient4Unity(brokerHostname, brokerPort, false, null);
        string clientId = Guid.NewGuid().ToString();

        client.Connect(clientId);
    }


    void Update()
    {
        //received data
        while (client.Count() > 0  && send == false)
        {
            string s = client.Receive();
            Debug.Log(s);
            position.text = s;

            if (s != oldmessage)
            {
                //sendaudrino.GetComponent<SendingAudrino>().sendmessage(s);
                SendingAudrino.sendmessage(s);
                oldmessage = s;
            }
        }

        //if(!Message.Equals(PrevMsg))
        //client.Publish(topic, System.Text.Encoding.ASCII.GetBytes(Message));

       // PrevMsg = Message;
    }


    public void SendString( string data)
    {
        if (send)
        {
            Debug.Log("message sent to MQTT: " + data);
            client.Publish(topic, System.Text.Encoding.ASCII.GetBytes(data));
        }
    }



   
}
