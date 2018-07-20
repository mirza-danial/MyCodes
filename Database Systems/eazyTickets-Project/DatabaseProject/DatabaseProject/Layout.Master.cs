using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;
using DatabaseProject;
using System.Data;

namespace DatabaseProject
{
    public partial class Layouy : System.Web.UI.MasterPage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if(Session["user"]!=null)
            {
                myDAL objmyDAl = new myDAL();
                String userId = Session["user"].ToString();
                int result = 0;
                int found = 1;
                found = objmyDAl.getEventCount_DAL(userId, ref result);
                if (found != 1)
                {
                    //execption
                }
                else
                {
                    if(result>0)
                    {
                        notificcationBadge.Text = result.ToString();
                       
                    }
                    else
                    {
                        NumOfEvents.Text = "No event near you";
                    }
                    DataTable dt=new DataTable();
                    found = objmyDAl.findNearbyEvent_DAL(userId,ref dt);
                    if(found==1)
                    {
                        Notify.DataSource = dt;
                        Notify.DataBind();
                    }
                  
                }
            }
            if (Session["user"] != null)
            {
                myDAL objmyDal1 = new myDAL();
                String user = Session["user"].ToString();
                int f = 1;
                DataTable DT = new DataTable();
                f = objmyDal1.ShopingCart_DAL(user, ref DT);
                if (f == 1)
                {
                    list.DataSource = DT;
                    list.DataBind();
                }

            }
        }
        protected void Logout_Click(object sender, EventArgs e)
        {
            String name = Session["user"].ToString();
            Session["user"] = null;
            Session["type"] = null;
            Drop(name);
            
            Response.Redirect("./Home.aspx");
        }
        
        protected void Drop(String name)
        {
           
                String User =name;
                int found = 1;
                myDAL objmyDal1 = new myDAL();
                found = objmyDal1.dropCart_DAL(User);
                if (found == 1)
                {
                    Response.Redirect("./Home.aspx");
                }
                else
                {
                    Message.Text = "Error Accord";
                }
          
            
        }

        protected void DropCart_Click(object sender, EventArgs e)
        {
            String name = Session["user"].ToString();
            Drop(name);
            Response.Redirect(HttpContext.Current.Request.Url.ToString(), true);
        }

        protected void DropItem_Click(object sender, EventArgs e)
        {
            if (Session["user"] != null)
            {
                LinkButton b = sender as LinkButton;
                String TicketId = b.ToolTip.ToString();
                String User = Session["user"].ToString();
                int found = 1;
                myDAL objmyDal1 = new myDAL();
                found = objmyDal1.dropItem_DAL(User, TicketId);
                if(found==1)
                {
                    Message.Text = "Successful removal ";
                    Response.Redirect(HttpContext.Current.Request.Url.ToString(), true);
                }
                else
                {
                    Message.Text = "Error Accord";
                }
            }
        }

        protected void ConfirmOrder_Click(object sender, EventArgs e)
        {
            if (Session["user"] != null)
            {
                String User = Session["user"].ToString();
                int found = 1;
                myDAL objmyDal1 = new myDAL();
                found = objmyDal1.ConfirmOrder_DAL(User);
                if (found == 1)
                {
                    Response.Redirect("./Home.aspx");
                }
                else
                {
                    Message.Text = "Error Accord";
                }
                Response.Redirect(HttpContext.Current.Request.Url.ToString(), true);
            }
        }
    }
}