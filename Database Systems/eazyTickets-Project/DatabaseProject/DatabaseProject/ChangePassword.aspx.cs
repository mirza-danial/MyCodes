using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using DatabaseProject;
using System.Data;
using System.Web.UI.HtmlControls;

namespace DatabaseProject
{
    public partial class ChangePassword : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["user"] != null)
            {
                HtmlLink link = Page.Master.FindControl("layoutStyleSheet") as HtmlLink;
                link.Href = "css/secondary.css";
            }
        }
        protected void changePasswordButton_Click(object sender, EventArgs e)
        {
            myDAL objmyDAl = new myDAL();
            String InputEmail = Session["user"].ToString();
            String InputOPassword = OldPass.Text;
            String InputNPassword = NewPass.Text;

            bool flag = true;
            if (string.IsNullOrWhiteSpace(InputOPassword))
            {
                OldPass.CssClass = OldPass.CssClass + " redBorder";
                Message.Text = "Some important fields are empty!";
                Message.CssClass = "alert alert-danger alert-dismissible";
                flag = false;

            }
            if (string.IsNullOrWhiteSpace(InputNPassword))
            {
                flag = false;
                NewPass.CssClass = NewPass.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger alert-dismissible";
                Message.Text = "Some important fields are empty!";
            }
            if (flag)
            {
                int result = 0;
                int found = 1;
                found = objmyDAl.changePassword_DAL(InputEmail, InputOPassword, InputNPassword, ref result);
                if (found != 1)
                {
                    Message.Text = "Error connecting to server please try later";
                }
                else
                {
                    if (result == -1)
                    {
                        Message.CssClass = "alert alert-danger alert-dismissible";
                        Message.Text = "No such user found!";
                    }
                    else if (result == -2)
                    {
                        Message.CssClass = "alert alert-danger alert-dismissible";
                        Message.Text = "Old password doesn't match!";
                    }
                    else if (result == 1)
                    {
                        Message.CssClass = "alert alert-success";
                        Message.Text = "Password changed successfully!";
                     }
       

                }
            }
        }
    }
}