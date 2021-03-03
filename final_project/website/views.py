import json

from flask import Blueprint, render_template, request, flash, jsonify
from flask_login import login_required, current_user

from .models import Todo
from . import db

views = Blueprint("views", __name__)


@views.route("/", methods=["GET", "POST"])
@login_required
def home():
    if request.method == "POST":
        todo = request.form.get("todo")

        if len(todo) < 1:
            flash("Todo is to short.", category="error")
        else:
            new_todo = Todo(data=todo, user_id=current_user.id)
            db.session.add(new_todo)
            db.session.commit()
            flash("Todo added!", category="success")

    return render_template("home.html", user=current_user)


@views.route("/delete-todo", methods=["POST"])
def delete_todo():
    data = json.loads(request.data)
    todo_id = data["todoId"]
    todo = Todo.query.get(todo_id)
    if todo:
        if todo.user_id == current_user.id:
            db.session.delete(todo)
            db.session.commit()
            flash("Todo deleted!", category="success")

    return jsonify({})
