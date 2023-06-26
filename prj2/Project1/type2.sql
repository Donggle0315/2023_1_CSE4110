select customer_id, past.total_count, past_year from (select * from past_deal where past_year='
' order by total_count desc limit 1) as past
