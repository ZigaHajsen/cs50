function deleteTodo(todoId) {
  fetch('/delete-todo', {
    method: 'POST',
    body: JSON.stringify({ todoId: todoId }),
  }).then((res) => {
    window.location.href = '/';
  });
}
