<%@ Page Title="" Language="C#" MasterPageFile="~/Layout.Master" AutoEventWireup="true" CodeBehind="ViewProfile.aspx.cs" Inherits="DatabaseProject.ViewProfile" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
    <style>
       .top-panel
       {
           border-bottom: 1px solid whitesmoke !important;
           padding-top:100px;
           padding-bottom:50px;
           padding-left:100px;
       }
       .id{
           font-size:25px !important;
           font-family:"Helvetica Neue", Helvetica, Arial, sans-serif;
       }
       .info,p{
            font-size:15px !important;
           font-family:"Helvetica Neue", Helvetica, Arial, sans-serif;
       }
    </style>
    <script type="text/javascript">
    function openModal() {
        $('#myModal').modal('show');
    }
    </script>
</asp:Content>


<asp:Content ID="Content4" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="top-panel">
        <span class="fa fa-user fa-5x"> <asp:Label CssClass="id" ID="UserId" runat="server"></asp:Label> </span>
       
    </div>
      <table class="table table-borderless">
    <thead>
      <tr>
        <th>First Name</th>
        <th>Last Name</th>
        <th>Phone Number</th>
        <th>City</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td><asp:Label CssClass="info" ID="Fname" runat="server"></asp:Label></td>
        <td><asp:Label CssClass="info" ID="Lname" runat="server"></asp:Label></td>
        <td><asp:Label CssClass="info" ID="Phone" runat="server"></asp:Label></td>
        <td><asp:Label CssClass="info" ID="City" runat="server"></asp:Label></td>
      </tr>
    </tbody>
  </table>
  <h1>Your Orders</h1>
  <asp:Repeater ID="Orders" runat="server">
      <HeaderTemplate>
          <table class="table table-borderless">
              <thead>
                  <th>Order#</th>
                  <th>Item Name</th>
                  <th>Cost</th>
                  <th>Quantity</th>
              </thead>
              <tbody>
      </HeaderTemplate>
      <ItemTemplate>
          <tr>
              <td><%# Eval("orderId")%></td>
              <td><%# Eval("Name")%></td>
              <td><%# Eval("cost")%></td>
              <td><%# Eval("amount")%></td>
              <td><asp:LinkButton CssClass="btn btn-warning" ID="ReveiwRating" ToolTip='<%# Eval("ticketId")%>' OnClick="RR_Click"   runat="server">Reveiw & Ratings</asp:LinkButton></td>
          </tr>
      </ItemTemplate>
      <FooterTemplate>
          </tbody>
          </table>
      </FooterTemplate>
  </asp:Repeater>
    <div class="modal fade" id="myModal">
                <div class="modal-dialog">
                  <div class="modal-content">
      
                    <!-- Modal Header -->
                    <div class="modal-header">
                      <h4 class="modal-title">Review & Rating</h4>
                      <button type="button" class="close" data-dismiss="modal">&times;</button>
                    </div>
        
                    <!-- Modal body -->
                    <div class="modal-body">
                        <asp:Label CssClass="nothide" ID="Id" runat="server" ></asp:Label>
                        <h4>Rate</h4>
                        <span class="starRating">
                            <asp:RadioButtonList ID="Rate" runat="server" RepeatDirection="Vertical" RepeatLayout="Flow">
                                <asp:ListItem Text="5" Value="5"></asp:ListItem>
                                <asp:ListItem Text="4 " Value="4"></asp:ListItem>
                                <asp:ListItem Text="3 " Value="3"></asp:ListItem>
                                <asp:ListItem Text="2 " Value="2"></asp:ListItem>
                                <asp:ListItem Text="1 " Value="1"></asp:ListItem>
                            </asp:RadioButtonList>
                        </span>
                        <asp:TextBox ID="Reveiw" CssClass="form-control" Placeholder="Write a review" runat="server"></asp:TextBox>
                        <br />
                        <asp:Button ID="Submit" CssClass="btn btn-block btn-primary" OnClick="Submit_Click" runat="server" Text="Submit" />
                        
                    </div>
        
                    <!-- Modal footer -->
                  
                   
                  </div>
                </div>
              </div>
    <asp:Label ID="Message" runat="server"></asp:Label>
    <footer class="py-5 bg-dark">
      <div class="container">
        <p class="m-0 text-center text-white">Copyright &copy; EasyTickets 2018</p>
      </div>
      <!-- /.container -->
    </footer>
</asp:Content>
