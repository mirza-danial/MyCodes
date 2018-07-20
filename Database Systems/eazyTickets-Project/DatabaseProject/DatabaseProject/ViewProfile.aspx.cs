using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using DatabaseProject;
using System.Web.UI.HtmlControls;
using System.Data;

namespace DatabaseProject
{
    public partial class ViewProfile : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["user"] != null)
            {
                HtmlLink link = Page.Master.FindControl("layoutStyleSheet") as HtmlLink;
                link.Href = "css/secondary.css";

                UserId.Text = Session["user"].ToString();
                myDAL objmyDAl = new myDAL();
                String InputEmail = Session["user"].ToString();
                String fname=null, lname=null, phone=null,city=null;
                int found = 1;
                found = objmyDAl.ViewUser_DAL(InputEmail,ref fname,ref lname,ref phone,ref city);
                if (found == 1)
                {
                    Fname.Text = fname;
                    Lname.Text = lname;
                    Phone.Text = phone;
                    City.Text = city;
                }

                found = 1;
                DataTable DT = new DataTable();
                found = objmyDAl.ViewOrders_DAL(InputEmail,ref DT);
                if (found == 1)
                {
                    Orders.DataSource = DT;
                    Orders.DataBind();
                }

            }
        }

        protected void Submit_Click(object sender, EventArgs e)
        {
            int TicketId = int.Parse(Id.Text.ToString());
            myDAL objmyDAl = new myDAL();
           
            String InputMessage = Reveiw.Text;
            int Rating = int.Parse(Rate.SelectedValue);
            Response.Write(Rating);
            bool flag = true;
            if (flag)
            {
                int result = 0;
                int found = 1;
                String User = Session["user"].ToString();
                found = objmyDAl.ReveiwRating_DAL(User, Rating, InputMessage, TicketId, ref result);
                if (found == 1)
                {
                    if (result == 1 || result==2)
                    {
                        Message.CssClass = "alert alert-success";
                        Message.Text = "Thanks for your review!";
                    }
                    else
                    {
                       
                    }
                }
                else
                {
                    Message.Text = "Error occured";
                }
            }
        }

        protected void RR_Click(object sender, EventArgs e)
        {
            ScriptManager.RegisterStartupScript(this, this.GetType(), "Pop", "openModal();", true);
            LinkButton b = sender as LinkButton;
            Id.Text =b.ToolTip.ToString();
        }
    }
}