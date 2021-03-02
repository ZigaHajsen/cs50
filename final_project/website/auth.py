import re

from flask import Blueprint, render_template, request, flash, redirect, url_for
from werkzeug.security import generate_password_hash, check_password_hash

from .models import User
from . import db

auth = Blueprint("auth", __name__)


@auth.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        email = request.form.get("email")
        password = request.form.get("password")

        user = User.query.filter_by(email=email).first()
        if user:
            if check_password_hash(user.password, password):
                flash("Logged in successfully!", category="success")
                return redirect(url_for("views.home"))
            else:
                flash("Incorrect credentials", category="error")
        else:
            flash("Incorrect credentials", category="error")

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
        user = User.query.filter_by(email=email).first()
        if user:
            flash("Email already exists.", category="error")
        elif not re.search(regex, email):
            flash("Email must be valid.", category="error")
        elif len(first_name) < 2:
            flash("Name to short.", category="error")
        elif password_1 != password_2:
            flash("Passwords do not match.", category="error")
        elif len(password_1) < 6:
            flash("Password must be at least 6 characters.", category="error")
        else:
            new_user = User(
                email=email,
                first_name=first_name,
                password=generate_password_hash(password_1, method="sha256"),
            )
            db.session.add(new_user)
            db.session.commit()
            flash("Account created!", category="success")
            return redirect(url_for("views.home"))

    return render_template("sign_up.html")