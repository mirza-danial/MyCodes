<%@ Page Title="" Language="C#" MasterPageFile="~/Layout.Master" AutoEventWireup="true" CodeBehind="Home.aspx.cs" Inherits="DatabaseProject.Home" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
<style>
    #HomeLink
    {

    }
    .contain {
        position: relative;
        width:200px;
        height:300px;
        display: inline-block;
        float: none;
    }
    
    .textblock {
        position: absolute;
        bottom: 5px;
        right: 5px;
        left:5px;
        background-color: rgba(0,0,0,0.5);
        color: white;
        padding-left: 20px;
        padding-right: 20px;
    }
    .row-fluid {
        overflow: auto;
        white-space: nowrap;
        padding-top:50px;
        padding-bottom:20px;
    }
    
    .image{
        width:200px !important;
        height:400px !important;
        
    }
    .display{
          margin-top:200px;
          background-color:#0b0c10;
    }
    .banner{
        width:100% !important;
        height:550px !important;
    }
    .text{
        position:center;
        text-align:center;
        color:white;
    }
</style>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">

    <img class="banner" src="images/bannerlight.png"  />

    
    <asp:Repeater ID="UpcomingEvents" runat="server">
        <HeaderTemplate>
            <div class="display">
            <h1 class="text">Upcoming events,movies and concerts</h1>
            <div class="row-fluid">
        </HeaderTemplate>
        <ItemTemplate>
                  <div class="contain" >
                 <img class="image" src="<%# Eval("ImageLink") %>"  alt="<%# Eval("name") %>" ID="img1">
                 <div class="textblock">
                  <h3 class="caption"><%# Eval("name") %></h3>
                  <h5 class="caption"><%# Eval("comingdate") %></h5>
                 </div>
                 </div>
         </ItemTemplate>
        <FooterTemplate>
           </div>
            </div>
        </FooterTemplate>
    </asp:Repeater>

   <footer class="py-5 bg-dark">
      <div class="container">
        <p class="m-0 text-center text-white">Copyright &copy; EasyTickets 2018</p>
      </div>
      <!-- /.container -->
    </footer>

 
   
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="NotificationsPlaceholder" runat="server">
    
</asp:Content>
