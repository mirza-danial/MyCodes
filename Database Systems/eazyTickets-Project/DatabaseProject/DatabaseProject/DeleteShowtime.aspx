<%@ Page Title="" Language="C#" MasterPageFile="~/adminLayout.Master" AutoEventWireup="true" CodeBehind="DeleteShowtime.aspx.cs" Inherits="DatabaseProject.DeleteShowtime" %>
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

    <h1>Delete Showtime</h1>

    <asp:Repeater ID="Repeater1" runat="server"
        DataSourceID="SqlDataSource1">
        <HeaderTemplate>
            <table class="table table-borderless">
                <thead>
                    <tr>
                        <th>Showtime ID</th>
                        <th>Movie ID</th>
                        <th>Cinema ID</th>
                        <th>Date/Time</th>
                        <th>Available Seats</th>
                        <th>Cost</th>
                        <th>Screening Type</th>
                    </tr>
                </thead>
        </HeaderTemplate>

        <ItemTemplate>
            <tbody>
                <tr>
                    <td>
                        <asp:Label CssClass="info" ID="showId" Text='<%# Eval("showId") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="movieId" Text='<%# Eval("movieId") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="cinemaId" Text='<%# Eval("cinemaId") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="date_time" Text='<%# Eval("date_time") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="availableSeats" Text='<%# Eval("availableSeats") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="cost" Text='<%# Eval("cost") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="ScreeningType" Text='<%# Eval("ScreeningType") %>' runat="server"></asp:Label></td>
                </tr>
            </tbody>
        </ItemTemplate>
        <FooterTemplate>
            </table>
        </FooterTemplate>
    </asp:Repeater>
    <asp:SqlDataSource ConnectionString="<%$ ConnectionStrings:sqlCon1 %>"
        ID="SqlDataSource1" runat="server"
        SelectCommand="SELECT showId, movieId, cinemaId,date_time, availableSeats, cost, ScreeningType
             From [Showtime]"></asp:SqlDataSource>
    <div class="container">
        <div class="row">
            <div class="center_div text-light">
                <p>Showtime ID</p>
                <asp:TextBox ID="ShowtimeID" CssClass=" form-control" runat="server" onkeypress=" valueInsert(this)" type="number"></asp:TextBox>
                <br />
                <asp:Button ID="ShowtimeDelete" CssClass="btn btn-warning btn-block btn-lg" runat="server" Text="Delete Showtime" OnClick=" DelShowtime_Click" />
                <br />
                <asp:Label ID="Message" runat="server"></asp:Label>
            </div>
        </div>
    </div>

</asp:Content>
