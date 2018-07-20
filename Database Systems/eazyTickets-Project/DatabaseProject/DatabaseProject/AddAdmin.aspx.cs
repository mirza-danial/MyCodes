using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace DatabaseProject
{
    public partial class AddAdmin : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        protected void AddAdmin_Click(object sender, EventArgs e)
        {
            myDAL objmyDAl = new myDAL();
            int id = int.Parse(UserIDNo.Text);

            bool flag = true;

            if (int.MinValue == id)
            {
                flag = false;
                UserIDNo.CssClass = UserIDNo.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (flag)
            {
                int result = 0;
                int found = 1;
                found = objmyDAl.AddAdmin_DAL(id, ref result);
                if (found != 1)
                {
                    Message.Text = "Error connecting to server please try later";
                }
                else
                {
                    if (result == 0)
                    {
                        Message.CssClass = "alert alert-success";
                        Message.Text = "Admin has been added!";
                        Response.AddHeader("REFRESH", "1;URL=/adminHome.aspx");
                    }
                    else if (result == 1)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "User doesn't exist.";
                    }
                    else if (result == 2)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "User is already an admin.";
                    }
                }
            }
        }
    }
}