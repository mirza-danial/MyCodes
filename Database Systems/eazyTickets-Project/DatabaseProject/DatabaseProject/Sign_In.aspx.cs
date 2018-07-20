using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using DatabaseProject;
using System.Data;

namespace DatabaseProject
{
    public partial class Sigin_In : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        protected void LogInButton_Click(object sender, EventArgs e)
        {
            myDAL objmyDAl = new myDAL();
            String InputEmail = Email.Text;
            String InputPassword = Password.Text;
            Session["user"] = null;
            Session["type"] = null;


            bool flag = true;
            if (string.IsNullOrWhiteSpace(InputEmail))
            {
                Email.CssClass = Email.CssClass + " redBorder";
                Message.Text = "Some important fields are empty!";
                Message.CssClass = "alert alert-danger alert-dismissible";
                flag = false;

            }
            if (string.IsNullOrWhiteSpace(InputPassword))
            {
                flag = false;
                Password.CssClass = Password.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger alert-dismissible";
                Message.Text = "Some important fields are empty!";
            }
            if (flag)
            {
                int result = 0;
                int found = 1;
                found = objmyDAl.Login_DAL(InputEmail, InputPassword, ref result);
                if (found != 1)
                {
                    Message.Text = "Error connecting to server please try later";
                }
                else
                {
                    if (result == -1)
                    {
                        Message.CssClass = "alert alert-danger alert-dismissible";
                        Message.Text = "No user found";
                    }
                    else if (result == 0)
                    {
                        Message.CssClass = "alert alert-success";
                        Message.Text = "Logged in!";
                        Session["user"] = InputEmail;
                        Session["type"] = 1;
                        Response.Redirect("./Home.aspx");
                    }
                    else if (result == 3)
                    {
                        Message.CssClass = "alert alert-success";
                        Message.Text = "Logged in as admin!";
                        Session["user"] = InputEmail;
                        Session["type"] = 2;
                        Response.Redirect("./adminHome.aspx");
                    }

                }
            }
        }
    }
}