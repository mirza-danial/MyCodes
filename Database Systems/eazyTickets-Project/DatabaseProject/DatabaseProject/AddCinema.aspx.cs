using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace DatabaseProject
{
    public partial class AddCinema : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        protected void AddCinema_Click(object sender, EventArgs e)
        {
            myDAL objmyDAl = new myDAL();
            String cName = name.Text;
            String cLoc = location.Text;
            int cPhone = int.Parse(phoneno.Text);

            bool flag = true;
            if (string.IsNullOrWhiteSpace(cName))
            {
                name.CssClass = name.CssClass + " redBorder";
                Message.Text = "Some Fields are empty!";
                Message.CssClass = "alert alert-danger";
                flag = false;
            }
            if (string.IsNullOrWhiteSpace(cLoc))
            {
                flag = false;
                location.CssClass = location.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (int.MinValue == cPhone)
            {
                flag = false;
                phoneno.CssClass = phoneno.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (flag)
            {
                int result = 0;
                int found = 1;
                found = objmyDAl.AddCinema_DAL(cName, cLoc, cPhone, ref result);
                if (found != 1)
                {
                    Message.Text = "Error connecting to server please try later";
                }
                else
                {
                    if (result == 0)
                    {
                        Message.CssClass = "alert alert-success";
                        Message.Text = "Cinema has been added!";
                        Response.AddHeader("REFRESH", "1;URL=/adminHome.aspx");
                    }
                    else if (result == 1)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Cinema already exists.";
                    }
                }
            }
        }
    }
}