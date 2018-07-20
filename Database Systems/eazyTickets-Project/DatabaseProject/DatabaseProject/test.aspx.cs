using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace DatabaseProject
{
    public partial class test : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        protected void MyButtonHandler(Object sender, EventArgs e)
        {
            Button b = sender as Button;
            if (b != null)
            {
               
                Message.Text = "Button User Id " + b.Width.ToString() + " is pressed"  ;
                // logic based on cmdName
            }
        }

        protected void ButtonRepeater_ItemDataBound(object sender, RepeaterItemEventArgs e)
        {
          
        }
    }
}