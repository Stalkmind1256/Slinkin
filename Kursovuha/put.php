 <?php
// Получение тела PUT запроса
$body = file_get_contents('php://input');

// Вывод полученного тела запроса
echo "Received PUT data: " . $body;
?>
