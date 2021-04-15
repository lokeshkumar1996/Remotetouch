using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class playermove : MonoBehaviour
{ 
    float height ;
    float width ;
    int distanceallowed;
    Touch touch;
     
    // Start is called before the first frame update
    void Start()
    {
    Vector2 topRightCorner = new Vector2(1, 1);
     Vector2 edgeVector = Camera.main.ViewportToWorldPoint(topRightCorner);   
      height = edgeVector.y ;
      width = edgeVector.x ;

     // Cursor.visible = false;
      
    }

    // Update is called once per frame
    void Update()
    {
     
      //Debug.Log(height); 
      //Debug.Log(width); 
      //tpuch
     
     //Vector3 mouseWorldPosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);
     //mouseWorldPosition.z=0f;
     //transform.position = mouseWorldPosition;
      GameObject[] pasuepannel = GameObject.FindGameObjectsWithTag ("pausepanel");
      


      if (Input.touchCount > 0 )   
     {
        
         
         touch = Input.GetTouch(0);
         
         
         
        
         Vector3 touchPosition = Camera.main.ScreenToWorldPoint(touch.position);
         touchPosition.z = 0f;


         if(Vector2.Distance(transform.position, touchPosition) == 0)
            {distanceallowed = 1;}
        // if(Vector2.Distance(transform.position, touchPosition) > 0 && Vector2.Distance(transform.position, touchPosition) < 1)
          //  {distanceallowed = 5;}
            if(Vector2.Distance(transform.position, touchPosition) > 0)
            {distanceallowed = 20;}

         if(pasuepannel.Length == 0) 
         {
         
         if (touchPosition.x < (width) && touchPosition.x > -(width) && touchPosition.y < (height-4) && touchPosition.y > -(height)  ) 
         {
           
        if(Vector2.Distance(transform.position, touchPosition) < distanceallowed)
         //if (touchPosition.x < (touchPosition.x + 5) && touchPosition.x > (touchPosition.x - 5) && touchPosition.y < (touchPosition.y + 5) && touchPosition.y > -(touchPosition.y-5) ) 
         {
      
         
         transform.position = touchPosition;
         
         }
         
         //transform.position = touchPosition;
         
         }
         }
      }




    }
}
