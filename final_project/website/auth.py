import re

from flask import Blueprint, render_template, request, flash

auth = Blueprint("auth", __name__)


@auth.route("/login", methods=["GET", "POST"])
def login():
    return render_template("login.html")


@auth.route("/logout")
def logout():
    return "<p>Logout</p>"


@auth.route("/sign-up", methods=["GET", "POST"])
def sign_up():
    if request.method == "POST":
        email = request.form.get("email")
        first_name = request.form.get("first-name")
        password_1 = request.form.get("password-1")
        password_2 = request.form.get("password-2")

        regex = r"^[a-z0-9]+[\._]?[a-z0-9]+[@]\w+[.]\w{2,3}$"

        if not re.search(regex, email):
            flash("Email must be valid.", category="error")
        elif len(first_name) < 2:
            flash("Name to short.", category="error")
        elif password_1 != password_2:
            flash("Passwords do not match.", category="error")
        elif len(password_1) < 6:
            flash("Password must be at least 6 characters.", category="error")
        else:
            flash("Account created!", category="success")

    return render_template("sign_up.html")