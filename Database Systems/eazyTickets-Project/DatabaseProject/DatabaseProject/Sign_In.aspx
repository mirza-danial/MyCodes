<%@ Page Title="" Language="C#" MasterPageFile="~/Layout.Master" AutoEventWireup="true" CodeBehind="Sign_In.aspx.cs" Inherits="DatabaseProject.Sigin_In" %>
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
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
     <div class="container">   

            <div class="row">
              
              <div class="center_div text-light" >
                  <h1>Sign in</h1>

                  <p>Email</p>
                  <asp:TextBox ID="Email" CssClass="form-control" Placeholder="Enter email" runat="server"></asp:TextBox>
                  <br/>
                  <p>Password</p>
                  <asp:TextBox ID="Password" CssClass="form-control" type="password" important="" Placeholder="Enter password" runat="server"></asp:TextBox>
                  <br/>
                  <asp:Button ID="LogIn" CssClass="btn btn-warning btn-block btn-lg" runat="server" Text="Sign in" OnClick="LogInButton_Click"/>
                  <br/>
                  <a href="Sign_Up.aspx" id="SignUpLink">Create Account</a>
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
