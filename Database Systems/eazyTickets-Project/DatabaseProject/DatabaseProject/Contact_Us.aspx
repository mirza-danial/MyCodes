<%@ Page Title="" Language="C#" MasterPageFile="~/Layout.Master" AutoEventWireup="true" CodeBehind="Contact_Us.aspx.cs" Inherits="DatabaseProject.Contact_Us" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
<style>
     .center_div{
    display:block;
    margin: 10% auto;
    margin-top:200px;  
    width:33%;
  
    }
</style>
</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="well center_div row">
    <h1>Contact Us</h1>
    <p>Email</p>

    <asp:TextBox ID="Email" CssClass=" form-control" Placeholder="Enter your email " runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>

    <br />
    <p>Message</p>

    <asp:TextBox ID="Comment" TextMode="MultiLine" CssClass=" form-control " Rows="5" Placeholder="Enter your message here" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>
    
    <br />
    <asp:Button ID="MessageSend" CssClass="btn btn-warning btn-block btn-lg" runat="server" Text="Send Message" OnClick=" MessageSend_Click" />
    <br />
    <asp:Label ID="Message" runat="server" Text=""></asp:Label>
    </div>
    <footer class="py-5 bg-dark">
      <div class="container">
        <p class="m-0 text-center text-white">Copyright &copy; EasyTickets 2018</p>
      </div>
      <!-- /.container -->
    </footer>
</asp:Content>
