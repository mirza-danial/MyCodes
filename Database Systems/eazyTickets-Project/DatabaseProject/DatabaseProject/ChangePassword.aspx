<%@ Page Title="" Language="C#" MasterPageFile="~/Layout.Master" AutoEventWireup="true" CodeBehind="ChangePassword.aspx.cs" Inherits="DatabaseProject.ChangePassword" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
    <style>
  .center_div{
    display:block;
    margin: 10% auto;
    margin-top:200px;  
    width:33%;
  
    }
    #SignUpLink{
        color:black;
    }
    .redBorder {
        border-color: red;
    }
    p,h1{
        color: black;
    }

    .redText{
        color:red;
    }
    .greenText{
        color:green;
    }
</style>
</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
     <div class="container">   

            <div class="row">
              
              <div class="center_div text-light" >
                  <h1>Change Password</h1>

                  <p>Current Password</p>
                  <asp:TextBox ID="OldPass" CssClass="form-control" type="password" Placeholder="Enter current password" runat="server"></asp:TextBox>
                  <br/>
                  <p>New Password</p>
                  <asp:TextBox ID="NewPass" CssClass="form-control" type="password" important="" Placeholder="Enter new password" runat="server"></asp:TextBox>
                  <br/>
                  <asp:Button ID="Apply" CssClass="btn btn-warning btn-block btn-lg" runat="server" Text="Apply changes" OnClick="changePasswordButton_Click"/>
                  <br/>
                  <br/>
                  <asp:Label ID="Message" runat="server" ></asp:Label>
              </div>
             
            </div>
        </div>
    <footer class="py-5 bg-dark">
      <div class="container">
        <p class="m-0 text-center text-white">Copyright &copy; EasyTickets 2018</p>
      </div>
      <!-- /.container -->
    </footer>
</asp:Content>
