select customer_id, past.total_money, past_year from (select * from past_deal where past_year='
' order by total_money desc limit 1) as past
