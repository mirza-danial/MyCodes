<%@ Page Title="" Language="C#" MasterPageFile="~/adminLayout.Master" AutoEventWireup="true" CodeBehind="DeleteConcert.aspx.cs" Inherits="DatabaseProject.DeleteConcert" %>
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

    <h1>Delete Concert</h1>

    <asp:Repeater ID="Repeater1" runat="server"
        DataSourceID="SqlDataSource1">
        <HeaderTemplate>
            <table class="table table-borderless">
                <thead>
                    <tr>
                        <th>Concert ID</th>
                        <th>Concert Venue</th>
                        <th>Day/Time</th>
                        <th>Performer</th>
                        <th>Organizers</th>
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
                        <asp:Label CssClass="info" ID="concertId" Text='<%# Eval("concertId") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="venue" Text='<%# Eval("venue") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="DayTime" Text='<%# Eval("DayTime") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="perfomer" Text='<%# Eval("performer") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="organizers" Text='<%# Eval("organizers") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="availableTickets" Text='<%# Eval("availableTickets") %>' runat="server"></asp:Label></td>
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
        SelectCommand="SELECT * from [Concert]"></asp:SqlDataSource>
    <div class="container">
        <div class="row">
            <div class="center_div text-light">
                <p>Concert ID</p>
                <asp:TextBox ID="ConcertID" CssClass=" form-control" runat="server" onkeypress=" valueInsert(this)" type="number"></asp:TextBox>
                <br />
                <asp:Button ID="ConcertDelete" CssClass="btn btn-warning btn-block btn-lg" runat="server" Text="Delete Concert" OnClick=" DelConcert_Click" />
                <br />
                <asp:Label ID="Message" runat="server"></asp:Label>
            </div>
        </div>
    </div>

</asp:Content>
