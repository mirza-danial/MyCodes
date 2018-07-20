using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;

namespace DatabaseProject
{
    public partial class Contact_Us : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["user"] != null)
            {
                HtmlLink link = Page.Master.FindControl("layoutStyleSheet") as HtmlLink;
                link.Href = "css/secondary.css";
            }
        }
        protected void MessageSend_Click(object sender, EventArgs e)
        {
            myDAL objmyDAl = new myDAL();
            String InputEmail = Email.Text;
            String InputMessage = Comment.Text;

            bool flag = true;
            if (string.IsNullOrWhiteSpace(InputEmail))
            {
                Email.CssClass = Email.CssClass + " redBorder";
                Message.Text = "Some Fields are empty!";
                Message.CssClass = "alert alert-danger";
                flag = false;
            }
            if (flag)
            {
                int result = 0;
                int found = 1;
                found = objmyDAl.MessageSend_DAL(InputEmail, InputMessage, ref result);
                if (found != 1)
                {
                    Message.Text = "Error connecting to server please try later";
                }
                else
                {
                    if (result == 0)
                    {
                        Message.CssClass = "alert alert-success";
                        Message.Text = "Your message has been sent!";
                        Response.AddHeader("REFRESH", "1;URL=/Home.aspx");
                        //Response.Redirect("./Home.aspx");
                    }
                    else if (result == 1)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Invalid email address provided.";
                    }
                }
            }
        }
    }
}