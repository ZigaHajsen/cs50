import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    """Add cash"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # add cash to user
        db.execute("UPDATE users SET cash=cash+:amount WHERE id=:id",
                   amount=request.form.get("cash"), id=session["user_id"])
        flash("Cash added")

        return redirect("/")
    else:
        return render_template("cash.html")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # get all stocks and group by symbol
    rows = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING total_shares > 0", user_id=session["user_id"])

    # calculate total price by stock
    holdings = []
    total = 0
    for row in rows:
        stock = lookup(row["symbol"])
        holdings.append({
            "symbol": stock["symbol"],
            "name": stock["name"],
            "shares": row["total_shares"],
            "price": usd(stock["price"]),
            "total": usd(stock["price"] * row["total_shares"])
        })
        total += stock["price"] * row["total_shares"]

    # calcualte all values
    result = db.execute(
        "SELECT cash FROM users WHERE id=:id", id=session["user_id"])
    cash = result[0]["cash"]
    total += cash

    return render_template("index.html", holdings=holdings, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # ensure stock symbol and number of shares was submitted
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("must provide stock symbol and number of shares", 403)

        # get stock
        stock = lookup(request.form.get("symbol"))

        # check is valid stock name provided
        if stock == None:
            return apology("Stock symbol not valid", 403)

        # calculate cost of transaction
        cost = int(request.form.get("shares")) * stock['price']

        # check if user has enough cash for transaction
        result = db.execute(
            "SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        if cost > result[0]["cash"]:
            return apology("you do not have enough cash for this transaction", 403)

        # update cash amount in users database
        db.execute("UPDATE users SET cash=cash-:cost WHERE id=:id",
                   cost=cost, id=session["user_id"])

        # add transaction to transaction database
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                   user_id=session["user_id"], symbol=stock["symbol"], shares=int(request.form.get("shares")), price=stock["price"])
        flash("Transaction successfull")

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT symbol, shares, price, transacted FROM transactions WHERE user_id=:user_id", user_id=session["user_id"])
    for i in range(len(transactions)):
        transactions[i]["price"] = usd(transactions[i]["price"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # ensure name of stock was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 403)

        # get stock
        stock = lookup(request.form.get("symbol"))

        # check is valid stock name provided
        if stock == None:
            return apology("Stock symbol not valid", 403)

        # stock name is valid
        else:
            return render_template("quoted.html", stock={
                'name': stock['name'],
                'symbol': stock['symbol'],
                'price': usd(stock['price'])
            })

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password", 403)

        # Ensure password was and confirm password match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password and confirm password must match", 403)

        # hash password
        hash = generate_password_hash(request.form.get("password"))

        # add user to database
        try:
            result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                                username=request.form.get("username"), hash=hash)

        # ensure username is unique
        except:
            return apology("username already exists", 403)

        # remember which user has logged in
        session["user_id"] = result

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # ensure stock symbol and number of shares was submitted
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("must provide stock symbol and number of shares", 403)

        # get stock
        stock = lookup(request.form.get("symbol"))

        # check is valid stock name provided
        if stock == None:
            return apology("Stock symbol not valid", 403)

        # group shares by symbol
        rows = db.execute(
            "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING total_shares > 0", user_id=session["user_id"])
        for row in rows:
            if row["symbol"] == request.form.get("symbol"):
                # check if enough shares
                if int(request.form.get("shares")) > row["total_shares"]:
                    return apology("not enough shares to sell", 403)

        # calculate profit of transaction
        profit = int(request.form.get("shares")) * stock['price']

        # update cash amount in users database
        db.execute("UPDATE users SET cash=cash+:profit WHERE id=:id",
                   profit=profit, id=session["user_id"])

        # add transaction to transaction database
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                   user_id=session["user_id"], symbol=stock["symbol"], shares=-1 * int(request.form.get("shares")), price=stock["price"])
        flash("Transaction successfull")

        return redirect("/")

    else:
        symbols = db.execute(
            "SELECT symbol FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING SUM(shares) > 0", user_id=session["user_id"])
        return render_template("sell.html", symbols=[symbol["symbol"] for symbol in symbols])


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
