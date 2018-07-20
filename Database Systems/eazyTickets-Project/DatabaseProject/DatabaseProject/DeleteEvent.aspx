<%@ Page Title="" Language="C#" MasterPageFile="~/adminLayout.Master" AutoEventWireup="true" CodeBehind="DeleteEvent.aspx.cs" Inherits="DatabaseProject.DeleteEvent" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
    <style>
        .center_div {
            display: block;
            margin: 10% auto;
            margin-top: 100px;
            width: 33%;
        }

        .redBorder {
            border-color: red;
        }


        .redText {
            color: red;
        }

        .greenText {
            color: green;
        }

        p, h1 {
            color: black;
        }
    </style>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">

    <h1>Delete Event</h1>

    <asp:Repeater ID="Repeater1" runat="server"
        DataSourceID="SqlDataSource1">
        <HeaderTemplate>
            <table class="table table-borderless">
                <thead>
                    <tr>
                        <th>Event ID</th>
                        <th>Event Name</th>
                        <th>Event Type</th>
                        <th>Organizers</th>
                        <th>Venue</th>
                        <th>Day/Time</th>
                        <th>Available Tickets</th>
                        <th>Cost</th>
                        <th>Image Link</th>
                    </tr>
                </thead>
        </HeaderTemplate>

        <ItemTemplate>
            <tbody>
                <tr>
                    <td>
                        <asp:Label CssClass="info" ID="eventId" Text='<%# Eval("eventId") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="eventName" Text='<%# Eval("eventName") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="eventType" Text='<%# Eval("eventType") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="organizers" Text='<%# Eval("organizers") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="venue" Text='<%# Eval("venue") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="Day_Time" Text='<%# Eval("Day_Time") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="ticketsAvailable" Text='<%# Eval("ticketsAvailable") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="cost" Text='<%# Eval("cost") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="ImageLink" Text='<%# Eval("ImageLink") %>' runat="server"></asp:Label></td>
                </tr>
            </tbody>
        </ItemTemplate>
        <FooterTemplate>
            </table>
        </FooterTemplate>
    </asp:Repeater>
    <asp:SqlDataSource ConnectionString="<%$ ConnectionStrings:sqlCon1 %>"
        ID="SqlDataSource1" runat="server"
        SelectCommand="SELECT *
             From [Event]"></asp:SqlDataSource>
    <div class="container">
        <div class="row">
            <div class="center_div text-light">
                <p>Event ID</p>
                <asp:TextBox ID="EventID" CssClass=" form-control" runat="server" onkeypress=" valueInsert(this)" type="number"></asp:TextBox>
                <br />
                <asp:Button ID="EventDelete" CssClass="btn btn-warning btn-block btn-lg" runat="server" Text="Delete Event" OnClick=" DelEvent_Click" />
                <br />
                <asp:Label ID="Message" runat="server"></asp:Label>
            </div>
        </div>
    </div>

</asp:Content>
